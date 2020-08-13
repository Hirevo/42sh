/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** quotes
*/

#include "reports.h"

void report_unmatched_quote(const char *line, size_t idx)
{
    eputstr(" |\n");
    eputstr(" | %s\n", line);
    eputstr(" | \e[91m\e[1m");
    for (size_t j = 0; j < idx; j++)
        eputstr("~");
    eputstr("^ error: unmatched quote.\e[0m\n");
    eputstr(" |\n");
}
