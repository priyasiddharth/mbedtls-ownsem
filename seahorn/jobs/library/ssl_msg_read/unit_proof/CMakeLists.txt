# This file has been generated by the add_job script
add_library(ssl_msg_read_harness STATIC
  ssl_msg_read_harness.c)
target_include_directories(ssl_msg_read_harness
  PRIVATE ${MBEDTLS_DIR}/include/
  ${MBEDTLS_DIR}/library/
  ${PROJECT_SOURCE_DIR}/seahorn/include/
  ${SEAMOCK_ROOT}/include)
sea_link_libraries(ssl_msg_read_harness ssl_msg.opt.ir)
sea_link_libraries(ssl_msg_read_harness seahorn_mbedtls_util_lib.ir)
sea_overlink_libraries(ssl_msg_read_harness ssl_msg_read_env.ir)
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc(ssl_msg_read_harness)
sea_add_unsat_test(ssl_msg_read_harness)
