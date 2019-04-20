/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** cd
*/

#include "shell.h"

int check_dir(char *path)
{
    struct stat stats;

    if (stat(path, &stats) == -1)
        return -1;
    if (!S_ISDIR(stats.st_mode))
        return -2;
    return 0;
}

static int change_to(const char *path)
{
    char *oldpwd = getcwd(NULL, 0);
    if (chdir(path) == -1) {
        free(oldpwd);
        return eputstr("cd: can't change to target directory.\n"), 1;
    }
    char *pwd = getcwd(NULL, 0);
    setenv("OLDPWD", oldpwd, 1);
    setenv("PWD", pwd, 1);
    free(oldpwd);
    free(pwd);
    return 0;
}

static int move_dir2(vec_t *args, size_t count)
{
    int check = 0;

    if (count == 2 && lstr_equals(lvec_at(args, 1), "-")) {
        char *oldpwd = getenv("OLDPWD");
        if (oldpwd == NULL)
            return eputstr(": no such file or directory.\n"), 1;
        return change_to(oldpwd);
    } else if ((check = check_dir((count == 2) ? lvec_at(args, 1) :
                                                 lvec_at(args, 2))) == 0) {
        return change_to((count == 2) ? lvec_at(args, 1) : lvec_at(args, 2));
    } else {
        char *msg = ((check == -2) ? "%s: not a directory.\n" :
                                     "%s: no such file or directory.\n");
        return eputstr(
                   msg, (count == 2) ? lvec_at(args, 1) : lvec_at(args, 2)),
               1;
    }
    return 0;
}

int move_dir(vec_t *args)
{
    size_t count = lvec_size(args);
    if (count > 3 ||
        (count == 3 && lstr_equals(lvec_at(args, 1), "--") == false)) {
        return eputstr("cd: too many arguments.\n"), 1;
    } else if (count == 1 ||
        (count == 2 && lstr_equals(lvec_at(args, 1), "--"))) {
        char *home = getenv("HOME");
        if (home == NULL)
            return eputstr("cd: no home directory.\n"), 1;
        return change_to(home);
    } else if (move_dir2(args, count))
        return 1;
    return 0;
}

int cd_b(shell_t *shell, vec_t *args)
{
    int i = move_dir(args);
    char *str = get_alias_cmd(shell, "cwdcmd");

    if (str)
        quick_exec(shell, str);
    return i;
}
