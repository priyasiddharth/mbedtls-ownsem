#include "common.h" // allow access to private members of ssl_context
#include "mbedtls/ssl.h"
#include <ssl_misc.h>

#include <seahorn/seahorn.h>
#include <seahorn_config.h>
#include <seahorn_mbedtls_util.h>
#include <seahorn_util.h>
#include <seamock_unit_proof.h>

#include <stddef.h>

DEFINE_UNIT_PROOF(mbedtls_ssl_encrypt_buf) {
  // NOTE: setup the precondition
  HAVOC_SSL_CTX(ssl);
  HAVOC_ADD_CONF_TO_SSL_CTX(ssl);
  HAVOC_ADD_HANDSHAKE_TO_SSL_CTX(ssl);
  // setup transform
  mbedtls_ssl_transform transform;
  memhavoc(&transform, sizeof(mbedtls_ssl_transform));
  assume(transform.maclen <= GLOBAL_BUF_MAX_SIZE);
  mbedtls_record rec;
  memhavoc(&rec, sizeof(mbedtls_record));
  assume(rec.data_len == REC_DATA_LEN);
  rec.buf = (unsigned char *)malloc(GLOBAL_BUF_MAX_SIZE);
  rec.data_offset = 0;
  assume((transform.ivlen - (rec.data_len + 1) % transform.ivlen) <=
         MAX_PAD_LEN);
  // setup incoming & outgoing data
  init_incoming_buf(&ssl);
  init_outgoing_buf(&ssl);
  // NOTE: call the SUT
  int rc = mbedtls_ssl_encrypt_buf(&ssl, &transform, &rec, NULL /* f_rng */,
                                   NULL /* p_rng */);
  // NOTE: Postcondition check
}

int main(void) {
  CALL_UNIT_PROOF(mbedtls_ssl_encrypt_buf);
  return 0;
}
