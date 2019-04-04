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
    printf("\033[0m 0: TurboSh        : ");
    turbosh_prompt(shell);
    printf("\n\033[0m 1: Bash           : ");
    bash_prompt(shell);
    printf("\n\033[0m 2: TCSH           : ");
    tcsh_prompt(shell);
    printf("\n\033[0m 3: minimalist     : ");
    minimalist_prompt(shell);
    printf("\n\033[0m 4: Tomato Ketchup : ");
    ketchup_prompt(shell);
    printf("\n\033[0m 5: Big Mac        : ");
    bigmac_prompt(shell);
    printf("\n\033[0m 6: Oh My Zsh      : ");
    oh_my_zsh(shell);
    printf("\n\033[0m 7: Mysh           : ");
    mysh(shell);
    printf("\n\033[0m 8: Mysh (lambda)  : ");
    mysh_lambda(shell);
    printf("\n\033[0m 9: Mysh (256-bit) : ");
    mysh_256(shell);
    printf("\n\033[0m10: Mysh (arrow)   : ");
    mysh_arrow(shell);
    printf("\n\033[0m");
}

int prompt(shell_t *shell, int args)
{
    (void)(args);
    show_prompt(shell);
    while (1) {
        my_putstr("\033[0mMake your choice: ");
        char *input = get_next_line(0);
        if (input == 0) {
            my_putstr("\nPrompt unchanged !\n");
            return 1;
        }
        if (*input != 0 && is_num(input)) {
            int chosen = atoi(input);
            if (chosen >= 0 && chosen < 11) {
                shell->prompt = chosen;
                setenv("PROMPT", input, 1);
                free(input);
                return 0;
            }
        }
        my_putstr("Error: invalid choice.\n");
        free(input);
    }
    return 0;
}
