/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** tmp
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tmp_file(shell_t *shell)
{
    char *name;
    char *edit;
    char *exec;
    int fd;

    if ((edit = getenv("EDITOR")) == NULL ||
        (name = strdup("/tmp/42sh-tmpXXXXXX")) == NULL ||
        (fd = mkstemp(name)) == -1 ||
        asprintf(&exec, "%s %s", edit, name) == -1)
        return;
    if (shell->line)
        dprintf(fd, "%s", shell->line);
    free(shell->line);
    my_putchar(10);
    quick_exec(shell, exec);
    if (shell->exit_code == 1)
        return;
    lseek(fd, SEEK_SET, 0);
    while ((shell->line = get_next_line(fd))) {
        printf("%s\n", shell->line);
        exec_line(shell, 1);
    }
    close(fd);
    init_prompt(shell);
}
