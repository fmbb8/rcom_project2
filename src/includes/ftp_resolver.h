#ifndef FTP_RESOLVER_H
#define FTP_RESOLVER_H
#include <stddef.h>

int resolve_hostname(const char *hostname, char *out_ip, size_t out_ip_size);

#endif