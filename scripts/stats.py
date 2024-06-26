#!/usr/bin/env python3

import os
import re
import subprocess
import csv
from collections import defaultdict
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

def run_ctest():
    os.chdir("build-rel")
    timing_info = defaultdict(list)

    for _ in range(1):
        result = subprocess.run(['ctest', '--schedule-random', '--output-log', 'ctest_log.txt'], universal_newlines=True)
        if result.returncode != 0:
            print(f"CTest failed with return code {result.returncode}")
            return None

        with open('ctest_log.txt', 'r') as file:
            for line in file:
                match = re.search(r'(?P<test_name>\w+)_harness_unsat_test.*Passed\s+([\d.]+)\s+sec', line)
                if match:
                    test_name = match.group('test_name')
                    time = float(match.group(2))
                    timing_info[test_name].append(time)

    avg_timing_info = {test: sum(times)/len(times) for test, times in timing_info.items()}
    os.chdir("..")
    return avg_timing_info

def count_code_lines(directory, file_patterns):
    code_lines = 0
    for foldername, _, filenames in os.walk(directory):
        for filename in filenames:
            if any(filename.endswith(pattern) for pattern in file_patterns):
                with open(os.path.join(foldername, filename), 'r', encoding='utf-8', errors='ignore') as file:
                    lines = file.readlines()
                non_comment_lines = [line for line in lines if not line.strip().startswith(("//", "/*", "*", "*/", "#")) and line.strip() != '']
                code_lines += len(non_comment_lines)
    return code_lines

def calculate_and_output_averages(data):
    total_env_lines =   sum(item['total_LOC'] for item in data)
    total_unit_proof_lines = sum(item['unit_proof_LOC'] for item in data)
    num_tests = len(data)

    avg_env_lines = total_env_lines / num_tests if num_tests != 0 else 0
    avg_unit_proof_lines = total_unit_proof_lines / num_tests if num_tests != 0 else 0

    print(f"Average lines of environment code: {avg_env_lines:.2f}")
    print(f"Average lines of unit proof code: {avg_unit_proof_lines:.2f}")


def plot_bargraph(data):
    # Convert your data into a Pandas DataFrame
    df = pd.DataFrame(data)
    df['test_name'] = df['test_name'].str.replace('ssl_msg_', '')

    # Melt the DataFrame to have test names as individual rows
    df_melted = df.melt(id_vars=['test_name'], value_vars=['average_ctest_running_time', 'total_LOC'], var_name='Metric', value_name='Value')
    # Set Pandas to display all rows of the DataFrame
    pd.set_option('display.max_rows', None)

    # Set Pandas to display all columns of the DataFrame
    pd.set_option('display.max_columns', None)

    # Optional: Set the width of each column to avoid line wrapping
    pd.set_option('display.width', None)

    print(df_melted)

    # melted the grouped bar plot
    plt.figure(figsize=(15,7))
    sns.barplot(x='test_name', y='Value', hue='Metric', data=df_melted, palette='deep')
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.savefig('bar_graph_test_time_and_LOC.pdf')

def main():
    timing_info = run_ctest()
    if not timing_info:
        print("No timing information collected.")
        return
    data = []
    with open('test_data.csv', mode='w', newline='') as csv_file:
        fieldnames = ['test_name', 'average_ctest_running_time', 'unit_proof_LOC', 'env_LOC', 'total_LOC']
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writeheader()

        for test_name, avg_run_time in timing_info.items():
            unit_proof_loc = count_code_lines(f"seahorn/jobs/library/{test_name}/unit_proof", [".c"])
            env_loc = count_code_lines(f"seahorn/jobs/library/{test_name}/env", [".cc"])
            env_c_loc = count_code_lines(f"seahorn/jobs/library/{test_name}/env_c", [".c"])
            row = {
                'test_name': test_name,
                'average_ctest_running_time': avg_run_time,
                'unit_proof_LOC': unit_proof_loc,
                'env_LOC': env_loc + env_c_loc,
                'total_LOC': unit_proof_loc + env_loc + env_c_loc
            }
            writer.writerow(row)
            data.append(row)
    calculate_and_output_averages(data)
    plot_bargraph(data)


if __name__ == "__main__":
    main()
