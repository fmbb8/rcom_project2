#ifndef FTP_URL_H
#define FTP_URL_H

typedef struct {
  char *user;
  char *password;
  char *host;
  char *path;
} ftp_url_t;

// Parse URL string like "ftp://[user:pass@]host/path"
// On success returns 0 and fills struct
// On failure returns -1
int parse_ftp_url(const char *url, ftp_url_t *out);

// Free memory allocated in ftp_url_t
void free_ftp_url(ftp_url_t *url);

#endif
