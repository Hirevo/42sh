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

static bool hist_trim_list(void *ctx, void *_elem, size_t idx)
{
    size_t val = *(size_t *)(ctx);
    bool kept = idx < val;
    char **elem = _elem;

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
    char *hist_size = getenv("HIST_SIZE");
    size_t i = 0;

    for (i = 0; hist_size && hist_size[i] >= '0' && hist_size[i] <= '9'; i++);
    size_t val = (hist_size && hist_size[i] != 0) ? atoi(hist_size) : 500;
    lvec_reverse(hist);
    lvec_filter(hist, hist_trim_list, &val);
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
    char *home = getenv("HOME");

    if (shell->hist.arr == NULL)
        return;
    char *path = path_join(home, HIST_FILE);
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    free(path);
    if (fd == -1)
        return;
    write_hist(shell, fd);
}

void add_hist_elem(shell_t *shell, char *line)
{
    // TODO: Fix this (this splitting removes duplicate spaces, even in quotes)
    char **payload = my_split_mulchar(line, " \t");

    if (payload == NULL)
        handle_error("calloc");
    lvec_push_back(shell->hist.arr, 1, payload);
    char *hist_size = getenv("HIST_SIZE");
    size_t i = 0;
    for (i = 0; hist_size && hist_size[i] >= '0' && hist_size[i] <= '9'; i++)
        ;
    size_t val = (hist_size && hist_size[i] != 0) ? atoi(hist_size) : 500;
    lvec_reverse(shell->hist.arr);
    lvec_filter(shell->hist.arr, hist_trim_list, &val);
    lvec_reverse(shell->hist.arr);
}

void init_history(shell_t *shell)
{
    char *home = getenv("HOME");

    shell->hist.cur = 0;
    shell->hist.arr = lvec_with_capacity(512);
    if (shell->hist.arr == 0 || home == NULL)
        return;
    char *path = path_join(home, HIST_FILE);
    if (path == 0)
        return;
    int fd = open(path, O_RDONLY);
    free(path);
    if (fd == -1)
        return;
    for (char *line = get_next_line(fd); line; line = get_next_line(fd)) {
        add_hist_elem(shell, line);
        free(line);
    }
    close(fd);
}
