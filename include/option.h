/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** option
*/

#pragma once

#include <stdbool.h>

#define DEF_OPTION(name, T)                                                   \
    typedef struct {                                                          \
        bool ok;                                                              \
        T value;                                                              \
    } Option##name

#define OPTION(name) Option##name
#define SOME(name, val) ((Option##name){.ok = true, .value = val})
#define NONE(name) ((Option##name){.ok = false})
#define IS_SOME(ret) ret.ok
#define IS_NONE(ret) (ret.ok == false)
#define OPT_UNWRAP(ret) ret.value
#define OPT_UNWRAP_OR(ret, def) ((IS_SOME(ret)) ? ret.value : def)
#define OPT_MAP(ret, func) ((IS_SOME(ret)) ? func(OPT_UNWRAP(ret)) : ret)
