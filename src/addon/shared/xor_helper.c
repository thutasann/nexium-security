#include "../include/xor_helpers.h"
#include <node_api.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Base64 encode
char *base64_encode(const unsigned char *input, size_t length) {
    BIO *bio, *b64;
    BUF_MEM *buffer;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // No newlines
    BIO_write(bio, input, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &buffer);

    char *output = (char *)malloc(buffer->length + 1);
    memcpy(output, buffer->data, buffer->length);
    output[buffer->length] = '\0';

    BIO_free_all(bio);

    return output;
}

// Base64 decode
unsigned char *base64_decode(const char *input, size_t *out_len) {
    BIO *bio, *b64;
    size_t input_len = strlen(input);
    unsigned char *output = (unsigned char *)malloc(input_len);

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_mem_buf(input, input_len);
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // No newlines
    *out_len = BIO_read(bio, output, input_len);

    BIO_free_all(bio);

    return output;
}

// Secure XOR encryption with key rotation
void xor_encrypt(const char *input, const char *key, unsigned char *output) {
    size_t input_len = strlen(input);
    size_t key_len = strlen(key);

    unsigned char rotated_key[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)key, key_len, rotated_key); // Initial hashed key

    for (size_t i = 0; i < input_len; ++i) {
        output[i] = input[i] ^ rotated_key[i % SHA256_DIGEST_LENGTH]; // Encrypt with current key
        rotated_key[i % SHA256_DIGEST_LENGTH] = output[i];            // Rotate key based on output
    }
}

// Secure XOR decryption with key rotation
void xor_decrypt(const unsigned char *input, size_t input_len, const char *key, char *output) {
    size_t key_len = strlen(key);

    unsigned char rotated_key[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)key, key_len, rotated_key); // Initial hashed key

    for (size_t i = 0; i < input_len; ++i) {
        unsigned char original_key = rotated_key[i % SHA256_DIGEST_LENGTH];
        output[i] = input[i] ^ original_key;              // Decrypt with current key
        rotated_key[i % SHA256_DIGEST_LENGTH] = input[i]; // Rotate key based on input
    }
    output[input_len] = '\0'; // Null-terminate output
}
