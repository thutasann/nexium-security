#include "../include/middleware_helpers.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <zlib.h>

/** Compress data using `zlib` */
napi_value CompressZlib(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    if (argc < 1) {
        napi_throw_error(env, NULL, "Data is required for compression");
        return NULL;
    }

    size_t input_length;
    napi_value input_value = args[0];
    napi_get_value_string_utf8(env, input_value, NULL, 0, &input_length);
    char *input = (char *)malloc(input_length + 1);
    napi_get_value_string_utf8(env, input_value, input, input_length + 1, NULL);

    // compress using zlib
    uLongf output_length = compressBound(input_length);
    unsigned char *output = (unsigned char *)malloc(output_length);

    if (compress(output, &output_length, (const unsigned char *)input, input_length) != Z_OK) {
        free(input);
        free(output);
        napi_throw_error(env, NULL, "Compression failed");
        return NULL;
    }

    napi_value result;
    napi_create_buffer_copy(env, output_length, output, NULL, &result);

    free(input);
    free(output);
    return result;
}

/** Decompress data using `zlib` */
napi_value DecompressZlib(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    if (argc < 1) {
        napi_throw_error(env, NULL, "Compressed data is required for decompression");
        return NULL;
    }

    size_t input_length;
    unsigned char *input;
    napi_get_buffer_info(env, args[0], (void **)&input, &input_length);

    // Decompress using zlib
    uLongf output_length = input_length * 4; // Initial guess for output size
    unsigned char *output = (unsigned char *)malloc(output_length);

    while (uncompress(output, &output_length, input, input_length) == Z_BUF_ERROR) {
        output_length *= 2;
        output = (unsigned char *)realloc(output, output_length);
    }

    napi_value result;
    napi_create_string_utf8(env, (const char *)output, output_length, &result);

    free(output);
    return result;
}
