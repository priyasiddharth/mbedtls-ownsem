# This file has been generated by the add_job script
add_library(many_buffers_harness STATIC
  many_buffers_harness.c)
target_compile_definitions(many_buffers_harness PRIVATE NUM_OUT_RECORDS=${NUM_OUT_RECORDS})
target_include_directories(many_buffers_harness
  PRIVATE 
  ${PROJECT_SOURCE_DIR}/seahorn/include/
  ${SEAMOCK_ROOT}/include)
#sea_link_libraries(many_buffers_harness ssl_msg.opt.ir)
#sea_link_libraries(many_buffers_harness seahorn_mbedtls_util_lib.ir)
#sea_overlink_libraries(many_buffers_harness many_buffers_env.ir)
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc(many_buffers_harness)
sea_add_unsat_test(many_buffers_harness)
    