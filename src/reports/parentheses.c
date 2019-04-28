/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** parentheses
*/

#include "reports.h"

void report_unmatched_parenthesis(const char *line, size_t idx)
{
    eputstr(" |\n");
    eputstr(" | %s\n", line);
    eputstr(" | \e[38;2;255;0;33m\e[1m");
    for (size_t j = 0; j < idx; j++)
        eputstr("~");
    eputstr("^ error: unmatched parenthesis.\e[0m\n");
    eputstr(" |\n");
}
