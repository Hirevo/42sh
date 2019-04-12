/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exec
*/

#include "shell.h"
#include <errno.h>

int exec_b(shell_t *shell, int args)
{
    (void)(args);
    errno = 0;
    execvp(shell->cur->av[1], shell->cur->av + 1);
    switch (errno) {
    case ENOEXEC:
        dprintf(2, "%s: Exec format error. Binary file not executable.\n",
            shell->cur->av[1]);
        break;
    case EPERM:
    case EACCES:
    case EISDIR:
        dprintf(2, "%s: Permission denied.\n", shell->cur->av[1]);
        break;
    case ENOENT:
    default:
        dprintf(2, "%s: Command not found.\n", shell->cur->av[1]);
        break;
    }
    return 0;
}
