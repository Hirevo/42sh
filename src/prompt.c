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

OPTION(CharPtr) get_hostname(void)
{
    char ret[512] = {0};

    if (gethostname(ret, 512) == -1)
        return NONE(CharPtr);
    return OPT_FROM_NULLABLE(CharPtr, strdup(ret));
}

static void get_tab_prompt(void (*tab_prompt[12])(Shell *))
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
    tab_prompt[10] = &mysh_arrow;
    tab_prompt[11] = &ps1_prompt;
}

void print_prompt(Shell *shell)
{
    void (*tab_prompt[12])(Shell *);

    get_tab_prompt(tab_prompt);
    if (shell->prompt >= 0 && shell->prompt < 12)
        tab_prompt[shell->prompt](shell);
    else
        tab_prompt[0](shell);
}

void get_prompt(Shell *shell)
{
    char *str = getenv("PROMPT");

    shell->prompt = 0;
    if (str != NULL)
        shell->prompt = strtol(str, NULL, 10);
}
