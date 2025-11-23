#include "includes/ftp_resolver.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>


int resolve_hostname(const char *hostname, char *out_ip, size_t out_ip_size) {
  struct hostent *he = gethostbyname(hostname);

  if (!he || !he->h_addr_list[0]) {
    fprintf(stderr, "DNS resolution failed for host: %s\n", hostname);
    return -1;
  }

  const char *ip = inet_ntop(AF_INET, he->h_addr_list[0], out_ip, out_ip_size);

  if (!ip) {
    perror("inet_ntop");
    return -1;
  }

  return 0;
}