/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exec
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void exec_process(vec_t *args)
{
    size_t ac = lvec_size(args);
    char **av = calloc(ac + 1, sizeof(char *));

    if (av == 0) {
        eputstr("could not allocate process' argv.\n");
        exit(1);
    }
    memcpy(av, args->arr, sizeof(char *) * ac);
    lvec_drop(args);
    errno = 0;
    execvp(av[0], av);
    switch (errno) {
    case ENOEXEC:
        eputstr("%s: Exec format error. Binary file not executable.\n", av[0]);
        break;
    case EPERM:
    case EACCES:
    case EISDIR:
        eputstr("%s: Permission denied.\n", av[0]);
        break;
    case ENOENT:
    default:
        eputstr("%s: Command not found.\n", av[0]);
        break;
    }
    exit(1);
}

unsigned int exec_action(shell_t *shell, unsigned int args)
{
    exec_status_t status = exec_pipeline(shell);

    (void)(args);
    if (shell->is_done) {
        free_shell(shell);
        exit(status.code);
    }
    for (size_t i = 0; shell->final[i]; i++)
        free(shell->final[i]);
    free(shell->final);
    free_commands(shell);
    free(shell->line);
    return status.code;
}

int format_commands(shell_t *shell)
{
    for (command_t *head = shell->commands; head; head = head->next) {
        for (size_t i = 0; i < lvec_size(head->av); i++) {
            lvec_set(head->av, i, format_arg(lvec_at(head->av, i)));
            if (lvec_at(head->av, i) == NULL)
                return -1;
        }
    }
    return 0;
}

static int set_error(shell_t *shell, int ret)
{
    shell->exit_code = ret;
    return ret;
}

unsigned int exec_line(shell_t *shell, unsigned int args)
{
    if (subst_history(shell, args) == -1 || parse_alias(shell) == -1 ||
        parse_vars(shell) == -1 || magic(shell) == -1 ||
        (shell->line = my_epurcommand(shell->line)) == NULL ||
        parse_stars(shell) == 1 ||
        (shell->line = my_epurstr(shell->line)) == NULL)
        return set_error(shell, 1);
    if (is_line_empty(shell->line))
        return 0;
    free(shell->last);
    shell->last = NULL;
    args = count_args(shell->line);
    shell->final = bufferize(shell->line, args);
    if (shell->final == NULL || set_commands(shell) == -1 ||
        set_redirects(shell) == -1 || check_error(shell) == -1 ||
        format_commands(shell) == -1)
        return set_error(shell, 1);
    shell->cur = shell->commands;
    return exec_action(shell, args);
}
