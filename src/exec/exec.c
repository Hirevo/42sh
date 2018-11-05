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

void exec_child(shell_t *shell)
{
    errno = 0;
    execvp(shell->cur->av[0], shell->cur->av);
    switch (errno) {
    case ENOEXEC:
        dprintf(2, "%s: Exec format error. Binary file not executable.\n",
            shell->cur->av[0]);
        exit(1);
        break;
    case EPERM:
    case EACCES:
    case EISDIR:
        dprintf(2, "%s: Permission denied.\n", shell->cur->av[0]);
        exit(1);
        break;
    case ENOENT:
    default:
        dprintf(2, "%s: Command not found.\n", shell->cur->av[0]);
        exit(1);
        break;
    }
}

int check_access(char **final, shell_t *shell)
{
    int i;
    int ret;
    struct stat stats;

    i = -1;
    if (is_path(final[0])) {
        if (stat(final[0], &stats) == 0)
            return compare_stats(&stats);
    }
    else
        while (shell->path != NULL && shell->path[++i] != NULL)
            if (stat(cat_path(shell->path, final[0], i), &stats) == 0) {
                ret = compare_stats(&stats);
                return (ret == 0) ? i : -2;
            }
    return -1;
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
    if (shell->exit_str)
        free(shell->exit_str);
    shell->exit_str = my_unsigned_to_char(status.code);
    if (shell->exit_str == NULL)
        exit(84);
    return status.code;
}

int format_commands(shell_t *shell)
{
    command_t *head;
    int i;

    head = shell->commands;
    while (head) {
        i = -1;
        while (head->av[++i])
            if ((head->av[i] = format_arg(head->av[i])) == NULL)
                return -1;
        head = head->next;
    }
    return 0;
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
    if ((shell->final = bufferize(
             shell->line, args = count_args(shell->line))) == NULL)
        return 1;
    if (set_commands(shell) == -1 || set_redirects(shell) == -1 ||
        check_error(shell) == -1 || format_commands(shell) == -1)
        return shell->exit_code = 1;
    shell->cur = shell->commands;
    args = exec_action(shell, args);
    return args;
}
