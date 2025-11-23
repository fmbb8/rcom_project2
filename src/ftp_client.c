#include "includes/ftp_url.h"
#include "includes/ftp_resolver.h"
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s ftp://[<user>:<password>@]<host>/<url-path>\n", argv[0]);
    return 1;
  }

  ftp_url_t url;

  if (parse_ftp_url(argv[1], &url) != 0) {
    return 1;
  }

  printf("Parsed Hostname: %s\n", url.host);
  printf("Parsed Path: %s\n", url.path);
  printf("Parsed User: %s\n", url.user);
  printf("Parsed Password: %s\n", url.password);

  char ip[64];
  if (resolve_hostname(url.host, ip, sizeof(ip)) == 0) {
    printf("Resolved IP: %s\n", ip);
  }
  free_ftp_url(&url);
  return 0;
}
