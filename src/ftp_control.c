#include "includes/ftp_control.h"
#include <arpa/inet.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int ftp_connect(const char *ip, int port) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket");
    return -1;
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);

  if (inet_pton(AF_INET, ip, &addr.sin_addr) != 1) {
    perror("inet_pton");
    close(sockfd);
    return -1;
  }

  if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("connect");
    close(sockfd);
    return -1;
  }

  return sockfd;
}

char *ftp_read_line(int sockfd) {
  char buf[2048];
  int idx = 0;

  while (idx < (int)sizeof(buf) - 1) {
    char c;
    int n = recv(sockfd, &c, 1, 0);
    if (n <= 0)
      return NULL;

    buf[idx++] = c;

    if (idx >= 2 && buf[idx - 2] == '\r' && buf[idx - 1] == '\n') {
      buf[idx - 2] = 0;
      return strdup(buf);
    }
  }
  return NULL;
}

int ftp_read_reply(int sockfd, char **out_reply) {
  char *line = ftp_read_line(sockfd);
  if (!line)
    return -1;

  int code = atoi(line);

  size_t cap = 4096;
  char *buffer = malloc(cap);
  if (!buffer) {
    free(line);
    return -1;
  }
  buffer[0] = 0;

  strncat(buffer, line, cap - strlen(buffer) - 1);
  strcat(buffer, "\n");

  int multiline = 0;
  if (strlen(line) >= 4 && line[3] == '-') {
    multiline = 1;
  }

  free(line);

  if (!multiline) {
    *out_reply = buffer;
    return code;
  }

  while (1) {
    line = ftp_read_line(sockfd);
    if (!line)
      break;

    size_t need =
        strlen(buffer) + strlen(line) + 2;
    if (need > cap) {
      cap *= 2;
      buffer = realloc(buffer, cap);
    }

    strcat(buffer, line);
    strcat(buffer, "\n");

    char code_check[5];
    snprintf(code_check, 5, "%d ", code);

    if (strncmp(line, code_check, 4) == 0) {
      free(line);
      break;
    }

    free(line);
  }

  *out_reply = buffer;
  return code;
}
int ftp_send_cmd(int sockfd, const char *cmd) {
  size_t len = strlen(cmd);
  ssize_t sent = send(sockfd, cmd, len, 0);
  return (sent == (ssize_t)len) ? 0 : -1;
}

int ftp_send_cmd_get_reply(int sockfd, char **out_reply, const char *fmt, ...) {
  char buffer[512];

  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  strncat(buffer, "\r\n", sizeof(buffer) - strlen(buffer) - 1);

  if (ftp_send_cmd(sockfd, buffer) < 0) {
    perror("send");
    return -1;
  }

  char *reply;
  int code = ftp_read_reply(sockfd, &reply);
  if (code < 0) {
    fprintf(stderr, "Failed to read reply.\n");
    return -1;
  }

  printf("%s", reply);
  *out_reply = reply;

  return code;
}

int ftp_parse_pasv(const char *reply, char *ip_out, size_t ip_len,
                   int *port_out) {
  const char *p = strchr(reply, '(');
  if (!p)
    return -1;
  p++;

  int h1, h2, h3, h4, p1, p2;

  if (sscanf(p, "%d,%d,%d,%d,%d,%d", &h1, &h2, &h3, &h4, &p1, &p2) != 6) {
    return -1;
  }

  snprintf(ip_out, ip_len, "%d.%d.%d.%d", h1, h2, h3, h4);
  *port_out = p1 * 256 + p2;

  return 0;
}

int ftp_quit(int sockfd) {
    char *reply;
    int code = ftp_send_cmd_get_reply(sockfd, &reply, "QUIT");
    free(reply);

    return (code == 221) ? 0 : -1;
}
