[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)][data]

[data]: https://colab.research.google.com/github/priyasiddharth/mbedtls-ownsem/blob/main/mbedtls_ownsem.ipynb

# embedTLS with Ownership

## Analysis
Detailed analysis of dataset is available in an accompanying [Jupyter Notebook][data] in Google Colab.

## HOWTO recreate dataset

1. Build the verification jobs
```
docker build -t verify-mbedtls . --file docker/verify-mbedtls.Dockerfile
```

2. Run benchmark and collect results
```
docker run  -e SEAHORN_ROOT_REL=/home/usea/seahorn  -it verify-mbedtls
```

In the docker container you will be in `/home/usea/verify-mbedtls`. From here, run the benchmark script.
```
bash scripts/run_benchmarks.sh
```

The results will be in five files. Copy these files to host for analysis.
```
'results_flight_append.json'
'results_write_records.json'
'results_write_handshake_shad.json'
'results_write_handshake_main.json'
'result_many_buffers.json'
```

## SEABMC sources

The modified SEABMC sources can be found in [this](https://github.com/priyasiddharth/seahorn/tree/ownsem) repo.
