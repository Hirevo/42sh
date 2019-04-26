/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** reports
*/

#pragma once

#include "shell.h"

void report_unmatched_quote(const char *line, size_t idx);
void report_redirect_missing_name(const char *line, size_t start, size_t end);
void report_unmatched_parenthesis(const char *line, size_t idx);
