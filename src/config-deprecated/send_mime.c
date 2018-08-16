/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** send_mime
*/

#include "get_next_line.h"
#include "my.h"
#include "server.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static char *ext(char *path)
{
    int i = strlen(path) - 1;

    while (i >= 0 && path[i] != '.')
        i -= 1;
    return path + i + 1;
}

static char *get_mime(int fd, char *ext)
{
    char *tmp = get_next_line(fd);
    char *ret;

    while (tmp) {
        if (!my_strncmp(tmp, ext, strlen(ext))) {
            ret = strdup(tmp + strlen(ext) + 1);
            free(tmp);
            return ret;
        }
        free(tmp);
    }
    return strdup("text/plain");
}

void send_mime(t_socket sock, char *path)
{
    char *ex = ext(path);
    char *mime;
    int fd;

    if (ex == NULL)
        return;
    fd = open(MIMETYPE, O_RDONLY);
    if (fd == -1)
        return;
    mime = get_mime(fd, ex);
    close(fd);
    write_client(sock, "Content-type: ");
    write_client(sock, (mime) ? mime : "");
    write_client(sock, CRLF);
    free(mime);
}
