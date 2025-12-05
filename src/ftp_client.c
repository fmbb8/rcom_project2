#include "includes/ftp_control.h"
#include "includes/ftp_data.h"
#include "includes/ftp_resolver.h"
#include "includes/ftp_url.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>

const char *ftp_basename(const char *path) {
  const char *slash = strrchr(path, '/');
  return slash ? slash + 1 : path;
}

void print_transfer_status(long long bytes_received, long long total_size, double elapsed_time) {
  double speed = (elapsed_time > 0) ? (bytes_received / 1024.0 / 1024.0) / elapsed_time : 0.0;
  
  if (total_size > 0) {
    int bar_width = 40;
    double progress = (double)bytes_received / total_size;
    int filled = (int)(progress * bar_width);
    
    printf("\r[");
    for (int i = 0; i < bar_width; i++) {
      if (i < filled) printf("=");
      else if (i == filled) printf(">");
      else printf(" ");
    }
    printf("] %.1f%% %.2f/%.2f MB - %.2f MB/s", 
           progress * 100.0,
           bytes_received / 1024.0 / 1024.0,
           total_size / 1024.0 / 1024.0,
           speed);
  } else {
    printf("\rReceived: %.2f MB - Speed: %.2f MB/s", 
           bytes_received / 1024.0 / 1024.0,
           speed);
  }
  fflush(stdout);
}

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

  int control = ftp_connect(ip, 21);
  if (control < 0) {
    printf("Failed to connect to FTP server.\n");
    return 1;
  }

  char *greeting;
  int err = ftp_read_reply(control, &greeting);
  if (err > 0) {
    printf("Server says: %s", greeting);
    free(greeting);
  } else {
    printf("Failed to read greeting.\n");
    close(control);
    return 1;
  }
  char *reply;

  int code = ftp_send_cmd_get_reply(control, &reply, "USER %s", url.user);
  if (code == 331) {
    code = ftp_send_cmd_get_reply(control, &reply, "PASS %s", url.password);
  }

  if (code != 230) {
    printf("Login failed with code: %d\n", code);
    close(control);
    return 1;
  }

  int passvCode = ftp_send_cmd_get_reply(control, &reply, "PASV");
  if (passvCode != 227) {
    printf("PASV command failed with code: %d\n", passvCode);
    close(control);
    return 1;
  }

  char ip_data[64];
  int data_port;

  if (ftp_parse_pasv(reply, ip_data, sizeof(ip_data), &data_port) < 0) {
    printf("Failed to parse PASV reply.\n");
    free(reply);
    close(control);
    return 1;
  }

  printf("Passive mode data address: %s:%d\n", ip_data, data_port);

  int data_sock = ftp_open_data_connection(ip_data, data_port);
  if (data_sock < 0) {
    printf("Failed to open data connection.\n");
    close(control);
    return 1;
  }
  printf("Data connection established to %s:%d\n", ip_data, data_port);
  ftp_send_cmd_get_reply(control, &reply, "TYPE I");
  code = ftp_send_cmd_get_reply(control, &reply, "RETR %s", url.path);

  if (code >= 400) {
    printf("Server refused RETR.\n");
    return 1;
  }
  
  long long file_size = ftp_parse_file_size(reply);
  
  const char *filename = ftp_basename(url.path);
  FILE *f = fopen(filename, "wb");
  if (!f) {
    perror("fopen");
    close(data_sock);
    close(control);
    return 1;
  }

  char buf[4096];
  int n;
  long long total_bytes = 0;
  
  struct timespec start, current;
  clock_gettime(CLOCK_MONOTONIC, &start);
  
  printf("Downloading %s", filename);
  if (file_size > 0) {
    printf(" (%.2f MB)", file_size / 1024.0 / 1024.0);
  }
  printf("...\n");

  while ((n = recv(data_sock, buf, sizeof(buf), 0)) > 0) {
    fwrite(buf, 1, n, f);
    total_bytes += n;
    
    if (total_bytes % (100 * 1024) < (long long)sizeof(buf)) {
      clock_gettime(CLOCK_MONOTONIC, &current);
      double elapsed = (current.tv_sec - start.tv_sec) + 
                       (current.tv_nsec - start.tv_nsec) / 1e9;
      print_transfer_status(total_bytes, file_size, elapsed);
    }
  }

  fclose(f);
  
  struct timespec end;
  clock_gettime(CLOCK_MONOTONIC, &end);
  double total_time = (end.tv_sec - start.tv_sec) + 
                      (end.tv_nsec - start.tv_nsec) / 1e9;
  
  printf("\n\nTransfer complete!\n");
  printf("Total size: %.2f MB\n", total_bytes / 1024.0 / 1024.0);
  printf("Transfer time: %.2f seconds\n", total_time);
  printf("Average speed: %.2f MB/s\n", (total_bytes / 1024.0 / 1024.0) / total_time);
  printf("\n");
  code = ftp_read_reply(control, &reply);
  printf("%s", reply);
  free(reply);

  if (ftp_quit(control) == 0) {
    printf("Disconnected gracefully.\n");
  } else {
    printf("QUIT failed.\n");
  }

  free_ftp_url(&url);
  close(data_sock);
  close(control);
  return 0;
}
