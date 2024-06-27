    output_flight_append='results_flight_append.json'
output_write_records='results_write_records.json'
output_write_handshake_shad='results_write_handshake_shad.json'
output_write_handshake_main='results_write_handshake_main.json'
output_many_buffers='result_many_buffers.json'

# Initialize variables
metric="BMC.solve" # Default value if metric is not provided

# Function to display usage
usage() {
    echo "Usage: $0 [-m metric]"
    exit 1
}

# Parse options
while getopts ":m:" opt; do
    case ${opt} in
        m )
            metric=$OPTARG
            ;;
        \? )
            usage
            ;;
    esac
done

# Shift arguments so that remaining arguments can be processed if needed
shift $((OPTIND -1))

# Use the metric variable in your script
echo "Metric: $metric"
# plot results
                                #${output_write_records} \
                            #     "write_records_shad" \
python3 scripts/plot.py --input ${output_flight_append} \
                                ${output_write_handshake_shad} \
                                ${output_write_handshake_main} \
                                ${output_many_buffers}  \
                        --parameter "${metric}" --job_names "flight_append_shad" \
                        "write_handshake_shad" \
                        "write_handshake_main" \
                        "many_buffers_main"      