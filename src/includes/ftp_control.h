#ifndef FTP_CONTROL_H
#define FTP_CONTROL_H
#include <stddef.h>

int ftp_connect(const char *ip, int port);

char *ftp_read_line(int sockfd);

int ftp_send_cmd(int sockfd, const char *cmd);

int ftp_send_cmd_get_reply(int sockfd,char **out_reply, const char *fmt, ...);

int ftp_read_reply(int sockfd, char **out_reply);

int ftp_parse_pasv(const char *reply, char *ip_out, size_t ip_len, int *port_out);

int ftp_quit(int sockfd);

#endif