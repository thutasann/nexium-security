#include "../include/middleware_helpers.h"
#include <ctype.h>
#include <node_api.h>
#include <stdlib.h>
#include <string.h>

/** Helper function for sanitize and escape */
char *sanitize_and_escape(const char *input) {
    if (!input)
        return NULL;

    size_t len = strlen(input);
    // Increase buffer size to accommodate more escape sequences
    char *output = (char *)malloc(len * 4 + 1); // Increased multiplier for safety
    if (!output)
        return NULL;

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        char c = input[i];
        switch (c) {
        // ... existing HTML escapes ...
        case '<':
            strcat(&output[j], "&lt;");
            j += 4;
            break;
        case '>':
            strcat(&output[j], "&gt;");
            j += 4;
            break;
        case '&':
            strcat(&output[j], "&amp;");
            j += 5;
            break;
        case '"':
            strcat(&output[j], "&quot;");
            j += 6;
            break;
        case '\'':
            strcat(&output[j], "&#39;");
            j += 5;
            break;
        // Add SQL injection protection
        case ';':
            output[j++] = '\\';
            output[j++] = ';';
            break;
        case '-': // Protect against comment attacks
            output[j++] = '\\';
            output[j++] = '-';
            break;
        case '/': // Protect against comment attacks
            output[j++] = '\\';
            output[j++] = '/';
            break;
        case '\\':
            output[j++] = '\\';
            output[j++] = '\\';
            break;
        case '%': // Protect against LIKE attacks
            output[j++] = '\\';
            output[j++] = '%';
            break;
        case '_': // Protect against LIKE attacks
            output[j++] = '\\';
            output[j++] = '_';
            break;
        default:
            if (isprint(c)) {
                output[j++] = c;
            }
            break;
        }
    }
    output[j] = '\0';
    return output;
}