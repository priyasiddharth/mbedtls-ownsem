# This file has been generated by the add_job script
set(UNROLL_BOUND 2)
add_library(ssl_msg_flight_transmit_harness STATIC
  ssl_msg_flight_transmit_harness.c)
target_compile_definitions(ssl_msg_flight_transmit_harness PRIVATE MBEDTLS_SSL_MAX_FRAGMENT_LENGTH)
target_include_directories(ssl_msg_flight_transmit_harness
  PRIVATE ${MBEDTLS_DIR}/include/
  ${MBEDTLS_DIR}/library/
  ${PROJECT_SOURCE_DIR}/seahorn/include/)
sea_link_libraries(ssl_msg_flight_transmit_harness ssl_msg.opt.ir)
sea_overlink_libraries(ssl_msg_flight_transmit_harness ssl_msg_flight_transmit_env.ir)
sea_attach_bc(ssl_msg_flight_transmit_harness)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(ssl_msg_flight_transmit_harness)
