#ifndef FTP_URL_H
#define FTP_URL_H

typedef struct {
  char *user;
  char *password;
  char *host;
  char *path;
} ftp_url_t;

int parse_ftp_url(const char *url, ftp_url_t *out);

void free_ftp_url(ftp_url_t *url);

#endif
