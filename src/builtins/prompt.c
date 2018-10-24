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
    printf("\x1b[0m0: TurboSh        : ");
    turbosh_prompt(shell);
    printf("\n\x1b[0m1: Bash           : ");
    bash_prompt(shell);
    printf("\n\x1b[0m2: TCSH           : ");
    tcsh_prompt(shell);
    printf("\n\x1b[0m3: minimalist     : ");
    minimalist_prompt(shell);
    printf("\n\x1b[0m4: Tomato Ketchup : ");
    ketchup_prompt(shell);
    printf("\n\x1b[0m5: Big Mac        : ");
    bigmac_prompt(shell);
    printf("\n\x1b[0m6: Oh My Zsh      : ");
    oh_my_zsh(shell);
    printf("\n\x1b[0m7: Mysh           : ");
    mysh(shell);
    printf("\n\x1b[0m8: Mysh (lambda)  : ");
    mysh_lambda(shell);
    printf("\n\x1b[0m9: Mysh (256-bit) : ");
    mysh_256(shell);
    printf("\n\x1b[0m");
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
        if (is_num(choice) && atoi(choice) >= 0 && atoi(choice) <= 9) {
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
