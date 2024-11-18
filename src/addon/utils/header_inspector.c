#include "../include/utils.h"
#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Helper function to block malicious headers @internal */
int is_insecure_header(const char *header_name) {
    const char *blocked_headers[] = {
        // Information Disclosure Headers
        "X-Insecure-Header",
        "X-Malicious-Header",
        "Server-Timing",
        "X-Powered-By",
        "X-AspNet-Version",
        "X-Runtime",

        // Debug/Internal Headers
        "X-Debug-Token",
        "X-Debug-Token-Link",
        "X-Internal-Server",

        // Proxy/Forwarding Headers
        "Via",
        "Forwarded",
        "X-Forwarded-For",
        "X-Forwarded-Host",
        "X-Forwarded-Proto",

        // Security Headers that shouldn't be modified by clients
        "X-Frame-Options",
        "X-XSS-Protection",
        "X-Content-Type-Options",
        "Content-Security-Policy",

        NULL};

    for (int i = 0; blocked_headers[i] != NULL; i++) {
        if (strcasecmp(header_name, blocked_headers[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

/** Validate Headers */
napi_value ValidateHeaders(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    if (argc < 1) {
        napi_throw_error(env, NULL, "Invalid number of arguments");
        return NULL;
    }

    bool is_valid = true;
    napi_value header_object = args[0];

    // check if the input is an object
    napi_valuetype type;
    napi_typeof(env, header_object, &type);
    if (type != napi_object) {
        napi_throw_error(env, NULL, "Expected an object");
        return NULL;
    }

    // get properties (headers)
    napi_value keys;
    napi_get_property_names(env, header_object, &keys);

    uint32_t length;
    napi_get_array_length(env, keys, &length);

    for (uint32_t i = 0; i < length; i++) {
        napi_value key;
        napi_get_element(env, keys, i, &key);

        size_t key_length;
        napi_get_value_string_utf8(env, key, NULL, 0, &key_length);
        char *header_name = (char *)malloc(key_length + 1);
        napi_get_value_string_utf8(env, key, header_name, key_length + 1, NULL);

        if (is_insecure_header(header_name)) {
            is_valid = false;
            free(header_name);
            break;
        }

        free(header_name);
    }

    napi_value result;
    napi_get_boolean(env, is_valid, &result);
    return result;
}

/** Add Security Header */
napi_value AddSecurityHeaders(napi_env env, napi_callback_info info) {
    napi_value result;
    napi_create_object(env, &result);

    // Adding Strict-Transport-Security header
    napi_value hsts_value;
    napi_create_string_utf8(env, "max-age=31536000; includeSubDomains; preload", NAPI_AUTO_LENGTH, &hsts_value);
    napi_set_named_property(env, result, "Strict-Transport-Security", hsts_value);

    // Adding Content-Security-Policy header
    napi_value csp_value;
    napi_create_string_utf8(env, "default-src 'self'; script-src 'self'; object-src 'none'; frame-ancestors 'none';", NAPI_AUTO_LENGTH, &csp_value);
    napi_set_named_property(env, result, "Content-Security-Policy", csp_value);

    // Adding X-Content-Type-Options header
    napi_value xcto_value;
    napi_create_string_utf8(env, "nosniff", NAPI_AUTO_LENGTH, &xcto_value);
    napi_set_named_property(env, result, "X-Content-Type-Options", xcto_value);

    // Adding X-Frame-Options header
    napi_value xfo_value;
    napi_create_string_utf8(env, "DENY", NAPI_AUTO_LENGTH, &xfo_value);
    napi_set_named_property(env, result, "X-Frame-Options", xfo_value);

    // Adding Referrer-Policy header
    napi_value rp_value;
    napi_create_string_utf8(env, "strict-origin-when-cross-origin", NAPI_AUTO_LENGTH, &rp_value);
    napi_set_named_property(env, result, "Referrer-Policy", rp_value);

    // Adding Permissions-Policy header
    napi_value pp_value;
    napi_create_string_utf8(env, "geolocation=(), microphone=(), camera=()", NAPI_AUTO_LENGTH, &pp_value);
    napi_set_named_property(env, result, "Permissions-Policy", pp_value);

    // Adding X-XSS-Protection header
    napi_value xxp_value;
    napi_create_string_utf8(env, "0", NAPI_AUTO_LENGTH, &xxp_value); // Disabled as modern browsers have better protections
    napi_set_named_property(env, result, "X-XSS-Protection", xxp_value);

    // Adding Cross-Origin-Opener-Policy header
    napi_value coop_value;
    napi_create_string_utf8(env, "same-origin", NAPI_AUTO_LENGTH, &coop_value);
    napi_set_named_property(env, result, "Cross-Origin-Opener-Policy", coop_value);

    // Adding Cross-Origin-Resource-Policy header
    napi_value corp_value;
    napi_create_string_utf8(env, "same-origin", NAPI_AUTO_LENGTH, &corp_value);
    napi_set_named_property(env, result, "Cross-Origin-Resource-Policy", corp_value);

    return result;
}