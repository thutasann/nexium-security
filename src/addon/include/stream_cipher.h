#ifndef STREAM_CIPHER_HELPERS
#define STREAM_CIPHER_HELPERS

#include <stdlib.h>

void rc4_key_setup(unsigned char *S, const unsigned char *key, size_t key_len);
void rc4_crypt(unsigned char *S, const unsigned char *input, unsigned char *output, size_t len);
char *stream_base64_encode(const unsigned char *input, size_t len);
unsigned char *stream_base64_decode(const char *input, size_t *out_len);

#endif