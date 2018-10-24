/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** prompt
*/

#include "prompt.h"
#include "get_next_line.h"
#include "shell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char *get_hostname(void)
{
    char *ret;
    int fd = open("/etc/hostname", O_RDONLY);

    if (fd == -1)
        return NULL;
    ret = get_next_line(fd);
    close(fd);
    return ret;
}

static void get_tab_prompt(void (*tab_prompt[9])(shell_t *))
{
    tab_prompt[0] = &turbosh_prompt;
    tab_prompt[1] = &bash_prompt;
    tab_prompt[2] = &tcsh_prompt;
    tab_prompt[3] = &minimalist_prompt;
    tab_prompt[4] = &ketchup_prompt;
    tab_prompt[5] = &bigmac_prompt;
    tab_prompt[6] = &oh_my_zsh;
    tab_prompt[7] = &mysh;
    tab_prompt[8] = &mysh_lambda;
    tab_prompt[9] = &mysh_256;
}

void print_prompt(shell_t *shell)
{
    void (*tab_prompt[10])(shell_t *);

    get_tab_prompt(tab_prompt);
    if (shell->prompt >= 0 && shell->prompt < 10)
        tab_prompt[shell->prompt](shell);
    else
        tab_prompt[0](shell);
}

void get_prompt(shell_t *shell)
{
    char *str;

    shell->prompt = 0;
    if ((str = getenv("PROMPT")) != NULL)
        shell->prompt = strtol(str, NULL, 10);
}
