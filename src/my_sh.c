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

void execute(Shell *shell)
{
    char *line = 0;

    if (shell->ioctl) {
        OPTION(CharPtr) opt = prompt_line(shell);
        if (IS_NONE(opt)) {
            return;
        } else {
            line = OPT_UNWRAP(opt);
        }
    } else {
        line = get_next_line(0);
    }
    if (line && shell->tty && shell->ioctl)
        writechar('\n');
    if (!line) {
        line = strdup("exit");
    }
    OPTION(CharPtr) opt = clear_comment(line);
    if (IS_NONE(opt)) {
        return;
    } else {
        line = OPT_UNWRAP(opt);
    }
    if (!is_line_empty(line)) {
        char *postcmd = get_alias_cmd(shell, "postcmd");
        if (postcmd) {
            quick_exec(shell, postcmd);
        }
        shell->exit_code = exec_line(shell, line, shell->tty);
        char *precmd = get_alias_cmd(shell, "precmd");
        if (precmd) {
            quick_exec(shell, precmd);
        }
    }
}

static int start_standard_shell(Shell *shell)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    while (1) {
        shell->w.cur = 0;
        init_prompt(shell);
        execute(shell);
    }
    if (shell->tty) {
        writestr("exit\n");
        if (shell->ioctl) {
            tcsetattr(0, TCSANOW, &shell->w.oterm);
            writestr(shell->w.rmkx);
        }
    }
    return shell->exit_code;
}

static int treat_arg(Shell *shell, int ac, char **av)
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
    char *ret = fmtstr("%d", (lvl && my_str_isnum(lvl)) ? atoi(lvl) + 1 : 1);
    setenv("SHLVL", ret, 1);
    free(ret);
}

int main(int ac, char **av)
{
    Shell shell;

    setenv("SHELL", av[0], 1);
    increase_shell_level();
    init_shell(&shell);
    shell.av = av + ((ac == 1) ? 0 : 1);
    if (ac == 1)
        return start_standard_shell(&shell);
    else
        return treat_arg(&shell, ac, av);
    return 0;
}
