/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** history
*/

#include "get_next_line.h"
#include "my.h"
#include "server.h"
#include "shell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static bool last_500(void *ctx, char **elem, size_t idx)
{
    bool kept = idx < 500;

    (void)(ctx);
    if (kept == false) {
        for (size_t i = 0; elem && elem[i]; i++)
            free(elem[i]);
        free(elem);
    }
    return kept;
}

void write_hist(shell_t *shell, int fd)
{
    vec_t *hist = shell->hist.arr;

    lvec_reverse(hist);
    lvec_filter(hist, (bool (*)(void *, void *, size_t))(last_500), 0);
    lvec_reverse(hist);
    for (size_t i = 0; i < hist->size; i++) {
        const char **payload = hist->arr[i];
        for (size_t j = 0; payload[j]; j++)
            dprintf(fd, i ? " %s" : "%s", payload[j]);
        dprintf(fd, "\n");
    }
    close(fd);
    free_hist(shell);
}

void save_history(shell_t *shell)
{
    char *line;

    if (shell->hist.arr == NULL || shell->home == NULL)
        return;
    line = calloc(512, sizeof(char));
    line[0] = 0;
    line = strcat(line, shell->home);
    if (shell->home[strlen(shell->home)] != '/')
        line[strlen(shell->home)] = '/';
    line[strlen(shell->home) + 1] = 0;
    line = strcat(line, HIST_FILE);
    const int fd = open(line, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return;
    free(line);
    write_hist(shell, fd);
}

int disp_hist(shell_t *shell, int args)
{
    vec_t *arr = shell->hist.arr;

    (void)(args);
    if (arr == NULL)
        return 0;
    for (size_t i = 0; i < arr->size; i++) {
        char **payload = arr->arr[i];
        printf("%6lu\t", i);
        for (size_t j = 0; payload[j]; j++)
            printf(i ? " %s" : "%s", payload[j]);
        printf("\n");
    }
    return 0;
}

void add_hist_elem(shell_t *shell, char *line)
{
    char **payload = my_split_mulchar(line, " \t");

    if (payload == NULL)
        handle_error("calloc");
    lvec_push_back(shell->hist.arr, 1, payload);
}

void init_history(shell_t *shell)
{
    int fd;
    char *line;

    shell->hist.cur = 0;
    shell->hist.arr = lvec_with_capacity(512);
    if (shell->hist.arr == 0 || shell->home == NULL)
        return;
    line = calloc(512, sizeof(char));
    if (line == NULL)
        handle_error("calloc");
    line[0] = 0;
    line = strcat(line, shell->home);
    if (shell->home[strlen(shell->home)] != '/')
        line[strlen(shell->home)] = '/';
    line[strlen(shell->home) + 1] = 0;
    line = strcat(line, HIST_FILE);
    if ((fd = open(line, O_RDONLY)) == -1)
        return;
    free(line);
    line = get_next_line(fd);
    while (line) {
        add_hist_elem(shell, line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
}
