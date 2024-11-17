#include "../include/middleware_helpers.h"
#include "../include/utils.h"
#include <node_api.h>
#include <stdlib.h>
#include <string.h>

// Dynamically passed blacklist arrays
const char **blacklisted_ips = NULL;
size_t blacklisted_ip_count = 0;

const char **malicious_domains = NULL;
size_t malicious_domain_count = 0;

// Helper function to Check if an IP address is blacklisted
bool is_ip_blacklisted(const char *ip) {
    for (size_t i = 0; i < blacklisted_ip_count; i++) {
        if (strcmp(ip, blacklisted_ips[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Helper function to Check if a domain is malicious
bool is_domain_malicious(const char *domain) {
    for (size_t i = 0; i < malicious_domain_count; i++) {
        if (strcmp(domain, malicious_domains[i]) == 0) {
            return true;
        }
    }
    return false;
}

// function to set blacklisted IPs
napi_value set_blacklisted_ips(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    napi_value array = args[0];
    napi_value item;
    uint32_t array_length;

    napi_get_array_length(env, array, &array_length);

    // Free old memory
    free(blacklisted_ips);
    blacklisted_ips = (const char **)malloc(array_length * sizeof(char *));
    blacklisted_ip_count = array_length;

    for (uint32_t i = 0; i < array_length; i++) {
        napi_get_element(env, array, i, &item);

        size_t str_length;
        napi_get_value_string_utf8(env, item, NULL, 0, &str_length);

        blacklisted_ips[i] = (char *)malloc((str_length + 1) * sizeof(char));
        napi_get_value_string_utf8(env, item, (char *)blacklisted_ips[i], str_length + 1, NULL);
    }

    return NULL;
}

// function to set malicious domains
napi_value set_malicious_domains(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    napi_value array = args[0];
    napi_value item;
    uint32_t array_length;

    napi_get_array_length(env, array, &array_length);

    free(malicious_domains);
    malicious_domains = (const char **)malloc(array_length * sizeof(char *));
    malicious_domain_count = array_length;

    for (uint32_t i = 0; i < array_length; i++) {
        napi_get_element(env, array, i, &item);

        size_t str_length;
        napi_get_value_string_utf8(env, item, NULL, 0, &str_length);

        malicious_domains[i] = (char *)malloc((str_length + 1) * sizeof(char));
        napi_get_value_string_utf8(env, item, (char *)malicious_domains[i], str_length + 1, NULL);
    }

    return NULL;
}

// wrapper function to filter requests
napi_value filter_request(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_value result;
    char ip[256];
    char domain[256];
    size_t ip_len, domain_len;

    // Parse arguments
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    if (argc < 2) {
        napi_throw_error(env, NULL, "Invalid arguments. Expected IP and Domain.");
        return NULL;
    }

    // Get IP address
    napi_get_value_string_utf8(env, args[0], ip, sizeof(ip), &ip_len);

    // Get Domain
    napi_get_value_string_utf8(env, args[1], domain, sizeof(domain), &domain_len);

    // Check blacklist and malicious domains
    bool blocked = is_ip_blacklisted(ip) || is_domain_malicious(domain);

    // Return true (blocked) or false (allowed)
    napi_get_boolean(env, blocked, &result);
    return result;
}
