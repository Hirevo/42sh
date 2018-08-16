/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** prompt
*/

#include "prompt.h"
#include "get_next_line.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>

static void show_prompt(shell_t *shell)
{
    printf("0 : TurboSh        : ");
    turbosh_prompt(shell);
    printf("\n1 : Bash           : ");
    bash_prompt(shell);
    printf("\n2 : TCSH           : ");
    tcsh_prompt(shell);
    printf("\n3 : minimalist     : ");
    minimalist_prompt(shell);
    printf("\n4 : Tomato Ketchup : ");
    ketchup_prompt(shell);
    printf("\n5 : Big Mac        : ");
    bigmac_prompt(shell);
    printf("\n6 : Oh My Zsh      : ");
    oh_my_zsh(shell);
    printf("\n7 : Mysh           : ");
    mysh(shell);
    printf("\n");
}

int prompt(shell_t *shell, int args)
{
    int stop;
    char *choice;

    (void)args;
    show_prompt(shell);
    stop = 0;
    while (!stop) {
        printf("Make your choice : ");
        fflush(stdout);
        if (!(choice = get_next_line(0)) && printf("\n"))
            return 1;
        if (is_num(choice) && atoi(choice) >= 0 && atoi(choice) <= 7) {
            shell->prompt = my_getnbr(choice);
            setenv("PROMPT", choice, 1);
            free(choice);
            return 0;
        }
        printf("Nope\n");
        free(choice);
    }
    return 0;
}
