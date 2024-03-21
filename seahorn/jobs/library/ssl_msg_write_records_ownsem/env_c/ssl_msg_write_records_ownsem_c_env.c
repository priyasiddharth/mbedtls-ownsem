#include "common.h" // allow access to private members of ssl_context
#include "mbedtls/ssl.h"

#include <seahorn/seahorn.h>
#include <seahorn_util.h>
#include <ssl_misc.h>

int mbedtls_ssl_decrypt_buf(mbedtls_ssl_context const *ssl,
                            mbedtls_ssl_transform *transform,
                            mbedtls_record *record) {
  int r = nd_int();
  assume(r <= 0);
  return r;
}

int mbedtls_ssl_encrypt_buf(mbedtls_ssl_context *ssl,
                            mbedtls_ssl_transform *transform,
                            mbedtls_record *rec,
                            int (*f_rng)(void *, unsigned char *, size_t),
                            void *p_rng) {
  int r = nd_int();
  assume(r == 0);
  if (r == 0) {
    unsigned char* data_start = rec->buf + rec->data_offset;
    size_t data_len = rec->data_len;
    //unsigned char* src = (unsigned  char*) malloc(data_len);
    //memhavoc(src, data_len);
    // memset(data_start, 0, data_len);
    //memcpy((unsigned long *) data_start, (unsigned long *)src, data_len);
    sea_printf("rec.buf:%x\n", rec->buf);
    size_t count = sea_get_shadowmem(TRACK_CUSTOM0_MEM, (char *)(rec->buf));
    sea_set_shadowmem(TRACK_CUSTOM0_MEM, (char *)(rec->buf), ++count);
    SEA_READ_CACHE(count, rec->buf);
    SEA_WRITE_CACHE(rec->buf, ++count);
  }
  size_t in_data_offset = rec->data_offset;
  rec->data_offset = nd_bool() ? in_data_offset : 0;
  SEA_DIE(rec->buf);
  return r;
}

int mbedtls_ssl_check_dtls_clihlo_cookie(mbedtls_ssl_context *ssl,
                                         const unsigned char *cli_id,
                                         size_t cli_id_len,
                                         const unsigned char *in, size_t in_len,
                                         unsigned char *obuf, size_t buf_len,
                                         size_t *olen) {
  int r = nd_int();
  assume(r <= 0);
  return r;
}
