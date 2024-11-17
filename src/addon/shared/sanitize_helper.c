#include "../include/middleware_hepers.h"
#include <ctype.h>
#include <node_api.h>
#include <stdlib.h>
#include <string.h>

/** Helper function for sanitize and escape */
char *sanitize_and_escape(const char *input) {
    if (!input)
        return NULL;

    size_t len = strlen(input);
    char *output = (char *)malloc(len * 2 + 1);
    if (!output)
        return NULL;

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        char c = input[i];
        switch (c) {
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