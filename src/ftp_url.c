#include "includes/ftp_url.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int parse_ftp_url(const char *url, ftp_url_t *out) {
    memset(out, 0, sizeof(*out));

    if (strncmp(url, "ftp://", 6) != 0) {
        fprintf(stderr, "Error: URL must start with ftp://\n");
        return -1;
    }

    const char *p = url + 6;
    const char *slash = strchr(p, '/');

    if (!slash) {
        out->host = strdup(p);
        out->path = strdup("");
    } else {
        out->host = strndup(p, slash - p);
        out->path = strdup(slash + 1);
    }

    out->user = strdup("anonymous");
    out->password = strdup("anonymous@");

    return 0;
}

void free_ftp_url(ftp_url_t *url) {
    if (!url) return;
    free(url->user);
    free(url->password);
    free(url->host);
    free(url->path);
}