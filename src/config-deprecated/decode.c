/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** decode
*/

#include "server.h"
#include <ctype.h>
#include <stdlib.h>

int urldecode(char *sSource, char *sDest)
{
    int nLength;

    nLength = 0;
    while (*sSource) {
        if (*sSource == '%' && sSource[1] && sSource[2] &&
            isxdigit(sSource[1]) && isxdigit(sSource[2])) {
            sSource[1] -=
                sSource[1] <= '9' ? '0' : (sSource[1] <= 'F' ? 'A' : 'a') - 10;
            sSource[2] -=
                sSource[2] <= '9' ? '0' : (sSource[2] <= 'F' ? 'A' : 'a') - 10;
            sDest[nLength] = 16 * sSource[1] + sSource[2];
            sSource += 3;
        }
        else
            sDest[nLength] = *sSource++;
        nLength++;
    }
    sDest[nLength] = '\0';
    return nLength;
}
