/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** send_file_http
*/

#include "my.h"
#include "server.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int read_file(char *path, char *ret, int size, t_socket client)
{
    int len;
    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        write_client(client, FB_RESP);
        return 1;
    }
    len = read(fd, ret, size);
    ret[len] = 0;
    close(fd);
    return 0;
}

static void send_length(t_socket sock, int size)
{
    char *toc = int_toc(size);

    write_client(sock, toc);
    free(toc);
}

void send_file_http(t_socket sock, char *path)
{
    char *buf;
    struct stat stats;

    if (stat(path, &stats) == -1) {
        write_client(sock, NF_RESP);
        return;
    }
    buf = calloc(stats.st_size + 1, sizeof(char));
    if (buf == NULL) {
        write_client(sock, ERROR_RESP);
        return;
    }
    if (read_file(path, buf, stats.st_size, sock))
        return;
    write_client(sock, HEAD_RESP);
    write_client(sock, "Content-length: ");
    send_length(sock, stats.st_size);
    write_client(sock, CRLF);
    send_mime(sock, path);
    write_client(sock, "\r\n");
    send(sock, buf, stats.st_size, 0);
    free(buf);
    free(path);
}
