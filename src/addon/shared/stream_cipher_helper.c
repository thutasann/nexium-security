#include "../include/stream_cipher.h"
#include <node_api.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RC4 Key Scheduling Algorithm (KSA)
void rc4_key_setup(unsigned char *S, const unsigned char *key, size_t key_len) {
    for (size_t i = 0; i < 256; i++) {
        S[i] = (unsigned char)i;
    }

    unsigned char j = 0;
    for (size_t i = 0; i < 256; i++) {
        j = j + S[i] + key[i % key_len];
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
}

// RC4 Pseudo-Random Generation Algorithm (PRGA)
void rc4_crypt(unsigned char *S, const unsigned char *input, unsigned char *output, size_t len) {
    unsigned char i = 0, j = 0;
    for (size_t n = 0; n < len; n++) {
        i = i + 1;
        j = j + S[i];
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        output[n] = input[n] ^ S[(S[i] + S[j]) % 256];
    }
}

// Base64 Encoding Function
char *stream_base64_encode(const unsigned char *input, size_t len) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_write(bio, input, len);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    char *base64String = (char *)malloc(bufferPtr->length + 1);
    memcpy(base64String, bufferPtr->data, bufferPtr->length);
    base64String[bufferPtr->length] = '\0';
    BIO_free_all(bio);
    return base64String;
}

// Base64 Decoding Function
unsigned char *stream_base64_decode(const char *input, size_t *out_len) {
    BIO *bio, *b64;
    size_t len = strlen(input);
    unsigned char *buffer = (unsigned char *)malloc(len);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_mem_buf(input, len);
    bio = BIO_push(b64, bio);
    *out_len = BIO_read(bio, buffer, len);
    BIO_free_all(bio);
    return buffer;
}
