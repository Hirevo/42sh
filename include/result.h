/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** result
*/

#pragma once

#include <stdbool.h>

#define DEF_RESULT(name, T, E)                                                \
    typedef struct {                                                          \
        bool ok;                                                              \
        union {                                                               \
            T value;                                                          \
            E error;                                                          \
        } variants;                                                           \
    } Result##name

#define RESULT(name) Result##name
#define OK(name, val) ((Result##name){.ok = true, .variants = {.value = val}})
#define ERR(name, err)                                                        \
    ((Result##name){.ok = false, .variants = {.error = err}})
#define IS_OK(ret) ret.ok
#define IS_ERR(ret) (ret.ok == false)
#define RES_UNWRAP(ret) ret.variants.value
#define RES_UNWRAP_ERR(ret) ret.variants.error
#define RES_UNWRAP_OR(ret, def) ((IS_OK(ret)) ? ret.variants.value : def)
