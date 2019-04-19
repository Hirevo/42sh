/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** autocompletion
*/

#pragma once

#include "shell.h"

typedef struct {
    char *token;
    bool is_command;
    bool in_quote;
} Token;

DEF_OPTION(Token, Token);

void autocomplete(shell_t *shell);
