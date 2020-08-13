/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** quotes
*/

#include "reports.h"

void report_redirect_missing_name(const char *line, size_t start, size_t end)
{
    eputstr(" |\n");
    eputstr(" | %s\n", line);
    eputstr(" | \e[91m\e[1m");
    for (size_t j = 0; j < start; j++)
        eputstr("~");
    for (size_t j = start; j < end; j++)
        eputstr("^");
    eputstr(" error: missing name for redirect.\e[0m\n");
    eputstr(" |\n");
}
