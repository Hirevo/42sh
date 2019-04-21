/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** init
*/

#include "builtins.h"
#include "my.h"
#include "shell.h"
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <term.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

void set_raw(struct termios *oterm)
{
    struct termios nterm;

    nterm = *oterm;
    nterm.c_lflag &= ~(ICANON | ECHO);
    nterm.c_cc[VTIME] = 0;
    nterm.c_cc[VMIN] = 0;
    if (tcsetattr(0, TCSANOW, &nterm) == -1)
        handle_error("tcsetattr");
}

void init_builtins(Shell *shell)
{
    shell->builtins = lhmap_with_capacity(19);
    lhmap_set(shell->builtins, "alias", alias_b);
    lhmap_set(shell->builtins, "unalias", unalias_b);
    lhmap_set(shell->builtins, "builtins", builtins_b);
    lhmap_set(shell->builtins, "cd", cd_b);
    lhmap_set(shell->builtins, "config", config_b);
    lhmap_set(shell->builtins, "dualcast", dualcast_b);
    lhmap_set(shell->builtins, "echo", echo_b);
    lhmap_set(shell->builtins, "env", env_b);
    lhmap_set(shell->builtins, "exec", exec_b);
    lhmap_set(shell->builtins, "exit", exit_b);
    lhmap_set(shell->builtins, "history", history_b);
    lhmap_set(shell->builtins, "parserll", parserll_b);
    lhmap_set(shell->builtins, "prompt", prompt_b);
    lhmap_set(shell->builtins, "set", set_b);
    lhmap_set(shell->builtins, "setenv", setenv_b);
    lhmap_set(shell->builtins, "unset", unset_b);
    lhmap_set(shell->builtins, "unsetenv", unsetenv_b);
    lhmap_set(shell->builtins, "where", where_b);
    lhmap_set(shell->builtins, "which", which_b);
}

void init_vars(Shell *shell)
{
    char *str = 0;

    shell->vars = lhmap_with_capacity(5);
    if (asprintf(&str, "%d", getpid()) == -1)
        handle_error("calloc");
    lhmap_set(shell->vars, "pid", str);
    if (asprintf(&str, "%d", getppid()) == -1)
        handle_error("calloc");
    lhmap_set(shell->vars, "ppid", str);
    if (asprintf(&str, "%d", getgid()) == -1)
        handle_error("calloc");
    lhmap_set(shell->vars, "gid", str);
    if (asprintf(&str, "%d", getpgrp()) == -1)
        handle_error("calloc");
    lhmap_set(shell->vars, "pgid", str);
    if (asprintf(&str, "%d", getsid(0)) == -1)
        handle_error("calloc");
    lhmap_set(shell->vars, "sid", str);
}

void init_shell(Shell *shell)
{
    srand(getpid() * time(NULL));
    shell->exit_code = 0;
    shell->fds = NULL;
    shell->is_done = 0;
    parse_rc(shell);
    init_history(shell);
    init_aliases(shell);
    init_vars(shell);
    init_builtins(shell);
    get_prompt(shell);
    init(shell);
}

void init(Shell *shell)
{
    shell->tty = isatty(0);
    if (shell->tty) {
        if (tcsetpgrp(0, getpgid(getpid()))) {
            perror("tcsetpgrp");
            return;
        }
        if (getenv("TERM") == NULL || setupterm(NULL, 0, NULL) == ERR) {
            shell->ioctl = 0;
            return;
        }
        shell->ioctl = tcgetattr(0, &shell->w.oterm) + 1;
        shell->w.smkx = tigetstr("smkx");
        shell->w.rmkx = tigetstr("rmkx");
        shell->w.clear = tigetstr("clear");
        shell->w.end = tigetstr("kend");
        shell->w.home = tigetstr("khome");
        shell->w.forw = tigetstr("cuf1");
        shell->w.backw = tigetstr("cub1");
        shell->w.upw = tigetstr("kcuu1");
        shell->w.downw = tigetstr("kcud1");
        shell->w.left = tigetstr("kcub1");
        shell->w.right = tigetstr("kcuf1");
        shell->line = NULL;
    }
}

void init_prompt(Shell *shell)
{
    shell->hist.cur = -1;
    shell->hist.cur_line = NULL;
    if (shell->tty) {
        get_prompt(shell);
        sauv_prompt(shell);
        print_prompt(shell);
    }
}
