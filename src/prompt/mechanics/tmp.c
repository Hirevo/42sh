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

void tmp_file(Shell *shell)
{
    char name[] = "/tmp/42sh-edit-XXXXXX";
    char *editor = getenv("EDITOR");
    int fd = (editor ? mkstemp(name) : -1);
    char *exec = ((fd != -1) ? fmtstr("%s %s", editor, name) : 0);

    if (editor == NULL || fd == -1 || exec == 0)
        return;
    if (shell->line)
        dprintf(fd, "%s", shell->line);
    free(shell->line);
    writechar('\n');
    quick_exec(shell, exec);
    if (shell->exit_code == 1)
        return;
    lseek(fd, SEEK_SET, 0);
    while ((shell->line = get_next_line(fd))) {
        printf("%s\n", shell->line);
        exec_line(shell, 1);
    }
    close(fd);
    remove(name);
    init_prompt(shell);
}
