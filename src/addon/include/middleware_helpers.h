#ifndef MIDDLEWARE_HELPERS
#define MIDDLEWARE_HELPERS

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// sanitize input
char *sanitize_and_escape(const char *input);

// filter_request
bool is_ip_blacklisted(const char *ip);
bool is_domain_malicious(const char *domain);

#endif