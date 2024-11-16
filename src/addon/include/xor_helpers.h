#ifndef X0R_HELPERS
#define X0R_HELPERS

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

char *base64_encode(const unsigned char *input, size_t length);
unsigned char *base64_decode(const char *input, size_t *out_len);
void xor_encrypt(const char *input, const char *key, unsigned char *output);
void xor_decrypt(const unsigned char *input, size_t input_len, const char *key, char *output);

#endif