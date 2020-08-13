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
    nterm.c_lflag &= ~(ICANON | ECHO | ISIG);
    nterm.c_cc[VTIME] = 0;
    nterm.c_cc[VMIN] = 0;
    if (tcsetattr(0, TCSANOW, &nterm) == -1)
        handle_error("tcsetattr");
}

void init_builtins(Shell *shell)
{
    shell->builtins = lhmap_with_capacity(20);
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
    lhmap_set(shell->builtins, "expand", expand_b);
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
    shell->vars = lhmap_with_capacity(9);
    lhmap_set(shell->vars, "pid", fmtstr("%d", getpid()));
    lhmap_set(shell->vars, "ppid", fmtstr("%d", getppid()));
    lhmap_set(shell->vars, "uid", fmtstr("%d", getuid()));
    lhmap_set(shell->vars, "euid", fmtstr("%d", geteuid()));
    lhmap_set(shell->vars, "gid", fmtstr("%d", getgid()));
    lhmap_set(shell->vars, "pgid", fmtstr("%d", getpgrp()));
    lhmap_set(shell->vars, "sid", fmtstr("%d", getsid(0)));
    lhmap_set(shell->vars, "exec_duration", strdup("0"));
    lhmap_set(shell->vars, "exec_duration_fmt", strdup("0 secs"));
}

void init_args(Shell *shell, int ac, char **av)
{
    shell->args = lvec_new();
    for (int i = 0; i < ac; i++) {
        if (av[i][0] == '-') {
            continue;
        }
        char *arg = strdup(av[i]);
        if (arg) {
            lvec_push_back(shell->args, 1, arg);
        }
    }
    if (lvec_size(shell->args) > 1) {
        free(lvec_pop_front(shell->args));
    }
}

void init_shell(Shell *shell, int ac, char **av)
{
    srand(getpid() * time(NULL));
    shell->exit_code = 0;
    shell->is_done = 0;
    parse_rc(shell);
    init_args(shell, ac, av);
    init_history(shell);
    init_aliases(shell);
    init_vars(shell);
    init_builtins(shell);
    get_prompt(shell);
    init(shell);
    // parse_config(".42sh_config.json");
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
        shell->w.backsp = tigetstr("kbs");
        shell->w.delete = tigetstr("kdch1");
        shell->w.actions = lhmap_with_capacity(8);
        lhmap_set(shell->w.actions, shell->w.left, action_cursor_left);
        lhmap_set(shell->w.actions, shell->w.right, action_cursor_right);
        lhmap_set(shell->w.actions, shell->w.upw, action_cursor_up);
        lhmap_set(shell->w.actions, shell->w.downw, action_cursor_down);
        lhmap_set(shell->w.actions, shell->w.home, action_cursor_home);
        lhmap_set(shell->w.actions, shell->w.end, action_cursor_end);
        lhmap_set(shell->w.actions, shell->w.delete, action_cursor_delete);
        lhmap_set(shell->w.actions, shell->w.backsp, action_cursor_backspace);
        lhmap_set(shell->w.actions, "\x7F", action_cursor_backspace);
        lhmap_set(shell->w.actions, "\t", action_autocomplete);
        lhmap_set(shell->w.actions, "\x0C", action_clear_term);
        lhmap_set(shell->w.actions, "\x03", action_interrupt);
        lhmap_set(shell->w.actions, "\x18\x05", action_open_editor);
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
