/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** show_signal
*/

#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>

int show_signal(int pid)
{
    int ret = 0;

    waitpid(pid, &ret, 0);
    if (WIFEXITED(ret) == 0) {
        diagnose_status(ret);
        return ret;
    } else {
        return WEXITSTATUS(ret);
    }
}
