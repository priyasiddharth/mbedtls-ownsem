# embedTLS with Ownership


## Create dataset

1. Build the verification jobs
```
docker build -t verify-mbedtls . --file docker/verify-mbedtls.Dockerfile
```

2. Run benchmark and collect results
```
docker run  -e SEAHORN_ROOT_REL=/home/usea/seahorn  -it verify-mbedtls
```

The results will be in four files

```
'results_flight_append.json'
'results_write_records.json'
'results_write_handshake_shad.json'
'results_write_handshake_main.json'
'result_many_buffers.json'
```
