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

static void show_prompt(Shell *shell)
{
    printf("\e[0m 0: TurboSh        : ");
    turbosh_prompt(shell);
    printf("\n\e[0m 1: Bash           : ");
    bash_prompt(shell);
    printf("\n\e[0m 2: TCSH           : ");
    tcsh_prompt(shell);
    printf("\n\e[0m 3: minimalist     : ");
    minimalist_prompt(shell);
    printf("\n\e[0m 4: Tomato Ketchup : ");
    ketchup_prompt(shell);
    printf("\n\e[0m 5: Big Mac        : ");
    bigmac_prompt(shell);
    printf("\n\e[0m 6: Oh My Zsh      : ");
    oh_my_zsh(shell);
    printf("\n\e[0m 7: Mysh           : ");
    mysh(shell);
    printf("\n\e[0m 8: Mysh (lambda)  : ");
    mysh_lambda(shell);
    printf("\n\e[0m 9: Mysh (256-bit) : ");
    mysh_256(shell);
    printf("\n\e[0m10: Mysh (arrow)   : ");
    mysh_arrow(shell);
    printf("\n\e[0m11: PS1            : ");
    ps1_prompt(shell);
    printf("\n\e[0m");
}

int prompt_b(Shell *shell, int args)
{
    (void)(args);
    show_prompt(shell);
    while (1) {
        writestr("\e[0mchoose a prompt: ");
        char *input = get_next_line(0);
        if (input == 0) {
            writestr("\nprompt unchanged !\n");
            return 1;
        }
        if (*input != 0 && is_num(input)) {
            int chosen = atoi(input);
            if (chosen >= 0 && chosen < 12) {
                shell->prompt = chosen;
                setenv("PROMPT", input, 1);
                free(input);
                return 0;
            }
        }
        writestr("error: invalid choice.\n");
        free(input);
    }
    return 0;
}
