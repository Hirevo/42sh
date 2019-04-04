/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** my_sh
*/

#include "get_next_line.h"
#include "my.h"
#include "parser_ll.h"
#include "shell.h"
#include <curses.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void diagnose_status(unsigned int status)
{
    if ((status % 128) == SIGSEGV)
        dprintf(2, "Segmentation fault");
    else if ((status % 128) == SIGFPE)
        dprintf(2, "Floating exception");
    else if ((status % 128) == SIGBUS)
        dprintf(2, "Bus error");
    else if ((status % 128) == SIGABRT)
        dprintf(2, "Aborted");
    else if ((status % 128) == SIGILL)
        dprintf(2, "Illegal instruction");
    else if ((status % 128) == SIGKILL)
        dprintf(2, "Killed");
    else if ((status % 128) == SIGTERM)
        dprintf(2, "Terminated");
    else if ((status % 128) == SIGPIPE)
        return;
    dprintf(2, (WCOREDUMP(status)) ? " (core dumped)\n" : "\n");
}

void reload_shell(shell_t *shell)
{
    char *path = getenv("PATH");

    if (path) {
        for (int k = 0; shell->path && shell->path[k]; k++)
            free(shell->path[k]);
        free(shell->path);
        shell->path = init_path(path);
    }
    shell->home = getenv("HOME");
    shell->current = get_current(shell->current, shell->home);
}

void execute(shell_t *shell)
{
    char *str;

    if (shell->ioctl)
        prompt_line(shell);
    else
        shell->line = get_next_line(0);
    if (shell->line && shell->tty && shell->ioctl)
        my_putchar('\n');
    if (!shell->line)
        shell->line = strdup("exit");
    clear_comment(shell);
    if (!is_line_empty(shell->line)) {
        if ((str = get_alias_cmd(shell, "postcmd")))
            quick_exec(shell, str);
        shell->exit_code = exec_line(shell, shell->tty);
        if ((str = get_alias_cmd(shell, "precmd")))
            quick_exec(shell, str);
    }
}

static int start_standard_shell(shell_t *shell)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    while (1) {
        shell->line = NULL;
        shell->w.cur = 0;
        init_prompt(shell);
        execute(shell);
    }
    if (shell->tty) {
        my_putstr("exit\n");
        if (shell->ioctl) {
            tcsetattr(0, TCSANOW, &shell->w.oterm);
            my_putstr(shell->w.rmkx);
        }
    }
    return shell->exit_code;
}

static int treat_arg(shell_t *shell, int ac, char **av)
{
    if (lstr_equals(av[1], "-c")) {
        if (ac >= 3) {
            signal(SIGINT, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            quick_exec(shell, strdup(av[2]));
        }
        return shell->exit_code;
    } else if (av[1][0] != '-') {
        int fd = open(av[1], O_RDONLY);
        if (fd == -1)
            return dprintf(2, "%s: No such file or directory\n", av[1]), 1;
        if (dup2(fd, 0) == -1)
            return 1;
        shell->tty = 0;
        shell->ioctl = 0;
        return start_standard_shell(shell);
    }
    return start_standard_shell(shell);
}

void increase_shell_level(void)
{
    char *lvl = getenv("SHLVL");
    char *ret = 0;

    asprintf(&ret, "%d", (lvl && my_str_isnum(lvl)) ? atoi(lvl) + 1 : 1);
    setenv("SHLVL", ret, 1);
    free(ret);
}

int main(int ac, char **av)
{
    shell_t shell;

    setenv("SHELL", av[0], 1);
    increase_shell_level();
    if (init_shell(&shell) == -1)
        return 84;
    shell.av = av + ((ac == 1) ? 0 : 1);
    if (ac == 1)
        return start_standard_shell(&shell);
    else
        return treat_arg(&shell, ac, av);
    return 0;
}
