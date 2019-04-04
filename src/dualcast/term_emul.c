/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** term_emul
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void del_last_char(int len_prompt, char **prompt, int *len)
{
    const int tmp = strlen(*prompt);

    *len = tmp - 11;
    if (tmp > len_prompt)
        *prompt = strndup(*prompt, tmp - 1);
}

void add_char_dc(char **prompt, char c, int *len)
{
    insert_char(prompt, c);
    *len = strlen(*prompt) - 11;
}

void del_prompt(int nb_char)
{
    int i;
    char space[nb_char + 1];

    i = 0;
    while (i < nb_char) {
        space[i] = ' ';
        i += 1;
    }
    space[i] = '\0';
    printf("\r%s", space);
}

void send_char(t_socket sock, char c)
{
    char *buf;
    char send[7];

    strcpy(send, "char:");
    send[5] = c;
    send[6] = '\0';
    write_socket(sock, send);
    read_socket(sock, &buf);
    free(buf);
}
