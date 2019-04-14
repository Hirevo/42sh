/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** get_next_line
*/

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char *line_cases(int fd, int *fd_s, char **final)
{
    int i = get_line_str(fd, final, READ_SIZE);

    if (i > 0)
        return get_final_line(final);
    else if (**final != 0) {
        *fd_s = -1;
        return *final;
    } else {
        free(*final);
        *final = NULL;
        return NULL;
    }
}

char *my_realloc(char *buffer, char *overflow)
{
    int i = -1;
    int j = -1;
    char *temp;

    while (overflow[++i])
        ;
    while (buffer[++j])
        ;
    temp = calloc(i + j + 1, sizeof(char));
    if (temp == NULL)
        return NULL;
    i = -1;
    j = 0;
    while (overflow[++i] != 0)
        temp[i] = overflow[i];
    while (buffer[j] != 0)
        temp[i++] = buffer[j++];
    temp[i] = 0;
    free(overflow);
    return temp;
}

int get_line_str(const int fd, char **final, int size)
{
    char buffer[size + 1];
    int chars = -1;

    while ((*final)[++chars] != 0)
        if ((*final)[chars] == 10)
            return 2;
    chars = read(fd, buffer, READ_SIZE);
    while (chars > 0) {
        buffer[chars] = 0;
        *final = my_realloc(buffer, *final);
        if (*final == NULL)
            return -1;
        chars = 0;
        while ((*final)[chars] != 0) {
            if ((*final)[chars] == 10)
                return 1;
            chars += 1;
        }
        chars = read(fd, buffer, READ_SIZE);
    }
    return 0;
}

char *get_final_line(char **overflow)
{
    char *final;
    int i = -1;
    int j = 0;

    while ((*overflow)[++i] != 10)
        ;
    final = calloc(i + 1, sizeof(char));
    if (final == NULL)
        return NULL;
    i = -1;
    while ((*overflow)[++i] != 10 && (*overflow)[i] != 0)
        final[i] = (*overflow)[i];
    final[i] = 0;
    if ((*overflow)[i] == 0)
        return final;
    while ((*overflow)[++i] != 0) {
        (*overflow)[j++] = (*overflow)[i];
        (*overflow)[i] = 0;
    }
    while ((*overflow)[j] != 0)
        (*overflow)[j++] = 0;
    return final;
}

char *get_next_line(const int fd)
{
    static char *final = NULL;
    static int fd_s = -1;

    if (fd == -1) {
        free(final);
        final = NULL;
        fd_s = -1;
        return NULL;
    }
    if (READ_SIZE <= 0)
        return NULL;
    if (final == NULL || (fd_s != fd && fd_s == -1)) {
        fd_s = fd;
        final = calloc(1, sizeof(char));
        if (final == NULL)
            return NULL;
        *final = 0;
    }
    return line_cases(fd, &fd_s, &final);
}
