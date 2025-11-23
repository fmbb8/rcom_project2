#ifndef FTP_RESOLVER_H
#define FTP_RESOLVER_H
#include <stddef.h>

// Resolve hostname to IPv4 string
// Returns 0 on success, -1 on error
int resolve_hostname(const char *hostname, char *out_ip, size_t out_ip_size);

#endif