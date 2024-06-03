#ifndef URL_H
#define URL_H

#include <stdbool.h>

/**
 * Normalizes a URL. 
 *
 * The `base` argument must be a normalized URL.
 * The `url` argument is the URL to be normalized.
 *
 * If `base` is "http://example.com/bar/baz" and `url` is "a/b/c", this function will return
 * "http://example.com/bar/a/b/c".
 */
char * normalizeURL(const char *base, const char *url);

/**
 * Returns true if the webpage URL in the second argument is internal to the website from the first
 * URL. Both URLs must be provided in normalized form.
 */
bool isInternalURL(const char *base, const char *to_validate);

#endif
