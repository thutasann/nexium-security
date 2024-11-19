#include "./include/utils.h"
#include <node_api.h>

/** Init Middleware Functions */
void InitMiddlewareFunctions(napi_env env, napi_value exports) {
    napi_value sanitize_fn;
    napi_create_function(env, NULL, 0, SanitizeInput, NULL, &sanitize_fn);
    napi_set_named_property(env, exports, "sanitizeInput", sanitize_fn);

    napi_value setIPsFn, setDomainsFn, filterFn;
    napi_create_function(env, NULL, 0, set_blacklisted_ips, NULL, &setIPsFn);
    napi_set_named_property(env, exports, "setBlacklistedIPs", setIPsFn);
    napi_create_function(env, NULL, 0, set_malicious_domains, NULL, &setDomainsFn);
    napi_set_named_property(env, exports, "setMaliciousDomains", setDomainsFn);
    napi_create_function(env, NULL, 0, filter_request, NULL, &filterFn);
    napi_set_named_property(env, exports, "filterRequest", filterFn);

    napi_value validate_headers, add_security_headers;
    napi_create_function(env, NULL, 0, ValidateHeaders, NULL, &validate_headers);
    napi_set_named_property(env, exports, "validateHeaders", validate_headers);
    napi_create_function(env, NULL, 0, AddSecurityHeaders, NULL, &add_security_headers);
    napi_set_named_property(env, exports, "addSecurityHeaders", add_security_headers);

    napi_value generate_csrf_token, validate_csrf_token;
    napi_create_function(env, NULL, 0, GenerateCSRFToken, NULL, &generate_csrf_token);
    napi_set_named_property(env, exports, "generateCSRFToken", generate_csrf_token);
    napi_create_function(env, NULL, 0, ValidateCSRFToken, NULL, &validate_csrf_token);
    napi_set_named_property(env, exports, "validateCSRFToken", validate_csrf_token);

    napi_value compress_zlib, decompress_zlib;
    napi_create_function(env, NULL, 0, CompressZlib, NULL, &compress_zlib);
    napi_set_named_property(env, exports, "compressZlib", compress_zlib);
    napi_create_function(env, NULL, 0, DecompressZlib, NULL, &decompress_zlib);
    napi_set_named_property(env, exports, "decompressZlib", decompress_zlib);
}
