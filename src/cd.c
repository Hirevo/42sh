/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** cd
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

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

int move_dir2(char **final, int ac)
{
    int check = 0;

    if (ac == 2 && lstr_equals(final[1], "-")) {
        char *oldpwd = getenv("OLDPWD");
        if (oldpwd == NULL)
            return eputstr(": no such file or directory.\n"), 1;
        return change_to(oldpwd);
    } else if ((check = check_dir((ac == 2) ? final[1] : final[2])) == 0) {
        return change_to((ac == 2) ? final[1] : final[2]);
    } else {
        char *msg = ((check == -2) ? "%s: not a directory.\n" :
                                     "%s: no such file or directory.\n");
        return eputstr(msg, (ac == 2) ? final[1] : final[2]), 1;
    }
    return 0;
}

int move_dir(char **final, int ac)
{
    if (ac > 3 || (ac == 3 && lstr_equals(final[1], "--") == false)) {
        return eputstr("cd: too many arguments.\n"), 1;
    } else if (ac == 1 || (ac == 2 && lstr_equals(final[1], "--"))) {
        char *home = getenv("HOME");
        if (home == NULL)
            return eputstr("cd: no home directory.\n"), 1;
        return change_to(home);
    } else if (move_dir2(final, ac))
        return 1;
    return 0;
}
