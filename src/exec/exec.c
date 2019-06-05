/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exec
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void exec_process(vec_t *args)
{
    size_t ac = lvec_size(args);
    char **av = calloc(ac + 1, sizeof(char *));

    if (av == 0) {
        eputstr("could not allocate process' argv.\n");
        exit(1);
    }
    memcpy(av, args->arr, sizeof(char *) * ac);
    lvec_drop(args);
    errno = 0;
    execvp(av[0], av);
    switch (errno) {
    case ENOEXEC:
        eputstr("%s: Exec format error. Binary file not executable.\n", av[0]);
        break;
    case EPERM:
    case EACCES:
    case EISDIR:
        eputstr("%s: Permission denied.\n", av[0]);
        break;
    case ENOENT:
    default:
        eputstr("%s: Command not found.\n", av[0]);
        break;
    }
    exit(1);
}

int exec_commands(Shell *shell, Command *commands)
{
    OPTION(Int) status = exec_pipeline(shell, commands);

    if (shell->is_done) {
        free_shell(shell);
        exit(OPT_UNWRAP_OR(status, 1));
    }
    free_commands(commands);
    return OPT_UNWRAP_OR(status, 1);
}

bool format_commands(Command *commands)
{
    for (Command *head = commands; head; head = head->next) {
        for (size_t i = 0; i < lvec_size(head->av); i++) {
            lvec_set(head->av, i, format_arg(lvec_at(head->av, i)));
            if (lvec_at(head->av, i) == NULL) {
                return false;
            }
        }
    }
    return true;
}

int exec_line(Shell *shell, char *line, bool to_save)
{
    char *current = line;
    OPTION(CharPtr) stage_result = NONE(CharPtr);

    stage_result = substitute_history(shell, current, to_save);
    if (IS_NONE(stage_result)) {
        shell->exit_code = 1;
        return 1;
    }
    current = OPT_UNWRAP(stage_result);
    stage_result = substitute_commands(shell, current);
    if (IS_NONE(stage_result)) {
        shell->exit_code = 1;
        return 1;
    }
    current = OPT_UNWRAP(stage_result);
    stage_result = substitute_aliases(shell, current);
    if (IS_NONE(stage_result)) {
        shell->exit_code = 1;
        return 1;
    }
    current = OPT_UNWRAP(stage_result);
    stage_result = substitute_vars(shell, current);
    if (IS_NONE(stage_result)) {
        shell->exit_code = 1;
        return 1;
    }
    current = OPT_UNWRAP(stage_result);
    stage_result = substitute_globs(shell, current);
    if (IS_NONE(stage_result)) {
        shell->exit_code = 1;
        return 1;
    }
    current = OPT_UNWRAP(stage_result);
    current = my_epurcommand(current);
    if (current == NULL) {
        shell->exit_code = 1;
        return 1;
    }
    current = my_epurstr(current);
    if (current == NULL) {
        shell->exit_code = 1;
        return 1;
    }
    if (is_line_empty(current))
        return 0;
    size_t args = estimate_fragment_count(current);
    vec_t *fragments = split_fragments(current, args);
    free(current);
    if (fragments == 0) {
        shell->exit_code = 1;
        return 1;
    }
    OPTION(CommandPtr) opt_commands = parse_commands(fragments);
    lvec_clear(fragments, true);
    lvec_drop(fragments);
    if (IS_NONE(opt_commands)) {
        shell->exit_code = 1;
        return 1;
    }
    Command *commands = OPT_UNWRAP(opt_commands);
    if (
        // clang-format off
        assign_redirects(commands) == false ||
        check_errors(commands) == false ||
        format_commands(commands) == false
        // clang-format off
    ) {
        shell->exit_code = 1;
        return 1;
    }
    shell->exit_code = exec_commands(shell, commands);
    return shell->exit_code;
}
