#include "includes/ftp_url.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_ftp_url(const char *url, ftp_url_t *out) {
  memset(out, 0, sizeof(*out));

  if (strncmp(url, "ftp://", 6) != 0) {
    fprintf(stderr, "Error: URL must start with ftp://\n");
    return -1;
  }

  const char *p = url + 6;
  const char *at = strchr(p, '@');
  if (at) {
    const char *colon = strchr(p, ':');

    if (colon && colon < at) {
      out->user = strndup(p, colon - p);
      out->password = strndup(colon + 1, at - colon - 1);
    } else {
      out->user = strndup(p, at - p);
      out->password = strdup("");
    }

    p = at + 1;
  } else {
    out->user = strdup("anonymous");
    out->password = strdup("anonymous");
  }
  const char *slash = strchr(p, '/');

  if (!slash) {
    out->host = strdup(p);
    out->path = strdup("");
  } else {
    out->host = strndup(p, slash - p);
    out->path = strdup(slash + 1);
  }
  return 0;
}

void free_ftp_url(ftp_url_t *url) {
  if (!url)
    return;
  free(url->user);
  free(url->password);
  free(url->host);
  free(url->path);
}