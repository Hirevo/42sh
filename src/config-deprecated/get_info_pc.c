/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** get_info_pc
*/

#include "get_next_line.h"
#include "my.h"
#include "server.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int parse_info_version(t_info_pc *ret, int fd)
{
    char *tmp = get_next_line(fd);

    ret->version = NULL;
    ret->os = NULL;
    while (tmp) {
        if (!strncmp("NAME=", tmp, 5))
            ret->os = strndup(tmp + 6, strlen(tmp) - 7);
        if (!strncmp("VERSION=", tmp, 8))
            ret->version = strndup(tmp + 9, strlen(tmp) - 10);
        free(tmp);
        tmp = get_next_line(fd);
    }
    return 0;
}

int parse_version(t_info_pc *ret)
{
    int fd = open("/etc/os-release", O_RDONLY);

    if (fd == -1)
        return 1;
    get_next_line(-1);
    parse_info_version(ret, fd);
    ret->plateforme = strdup("Linux");
    close(fd);
    fd = open("/etc/hostname", O_RDONLY);
    if (fd == -1)
        return 1;
    get_next_line(-1);
    ret->hostname = get_next_line(fd);
    close(fd);
    return 0;
}

int parse_ram(t_info_pc *ret, int i)
{
    int fd = open("/proc/meminfo", O_RDONLY);
    char *str = get_next_line(fd);

    if (fd == -1)
        return 1;
    while (str) {
        if (!strncmp(str, "MemTotal:", 9)) {
            i = 9;
            while (str[i] && !(str[i] >= '0' && str[i] <= '9'))
                i += 1;
            ret->mem_total = my_getnbr(str + i);
        }
        if (!strncmp(str, "MemAvailable:", 13)) {
            i = 13;
            while (str[i] && !(str[i] >= '0' && str[i] <= '9'))
                i += 1;
            ret->mem_available = my_getnbr(str + i);
        }
        free(str);
    }
    close(fd);
    return 0;
}

int parse_proco(t_info_pc *ret)
{
    int fd = open("/proc/cpuinfo", O_RDONLY);
    char *str = get_next_line(fd);
    int i;

    if (fd == -1)
        return 1;
    while (str) {
        if (!strncmp(str, "model name", 10)) {
            i = 10;
            while (str[i] && str[i] != ':')
                i += 1;
            i += 2;
            ret->proco = strdup(str + i);
            free(str);
            close(fd);
            return 0;
        }
        free(str);
    }
    close(fd);
    return 0;
}

t_info_pc *get_info(void)
{
    t_info_pc *ret = calloc(1, sizeof(t_info_pc));

    if (ret == NULL)
        return NULL;
    if (parse_version(ret))
        return NULL;
    if (parse_ram(ret, 0))
        return NULL;
    if (parse_proco(ret))
        return NULL;
    return ret;
}
