/*
** builtins.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:55:55 2017 Nicolas Polomack
** Last update Sat May  6 18:35:15 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"

int	exec_builtins3(t_shell *shell, int args, int *r, int i)
{
  if (my_strcmp(shell->cur->av[0], "alias") == 0)
    {
      if (args == 1)
        *r = disp_all_alias(shell);
      else if (args == 2)
        *r = disp_alias(shell, shell->cur->av[1]);
      else if (args == 3)
        *r = add_alias(shell, shell->cur->av[1], shell->cur->av[2]);
      else
	*r = my_print_err("alias: invalid syntax\n");
      i = 1;
    }
  else if (my_strcmp(shell->cur->av[0], "echo") == 0)
    {
      *r = echo_term(shell->cur->av + 1);
      i = 1;
    }
  else if (my_strcmp(shell->cur->av[0], "dualcast") == 0)
    {
      *r = launch_dualcast(shell, args);
      i = 1;
    }
  return (i);
}

int	exec_builtins2(t_shell *shell, int args, int *r, int i)
{
  if (my_strcmp(shell->cur->av[0], "cd") == 0)
    {
      *r = move_dir(shell->cur->av, args, shell);
      i = 1;
    }
  else if (my_strcmp(shell->cur->av[0], "setenv") == 0 ||
           my_strcmp(shell->cur->av[0], "unsetenv") == 0)
    {
      if (args == 3 && my_strcmp(shell->cur->av[0], "setenv") == 0)
        *r = set_env(shell->cur->av[1], shell->cur->av[2]);
      else if (args == 1 && my_strcmp(shell->cur->av[0], "setenv") == 0)
        *r = disp_env();
      else if (args == 2 && my_strcmp(shell->cur->av[0], "setenv") == 0)
        *r = set_env(shell->cur->av[1], "");
      else if (args == 1 && my_strcmp(shell->cur->av[0], "unsetenv") == 0)
        *r = my_print_err("unsetenv: Too few arguments.\n");
      else if (my_strcmp(shell->cur->av[0], "unsetenv") == 0)
	*r = unset_env(shell->cur->av);
      else
        *r = my_print_err(shell->cur->av[0]) +
          my_print_err(": Too many arguments.\n") - 1;
      reload_shell(shell);
      i = 1;
    }
  return (exec_builtins3(shell, args, r, i));
}

int	exec_builtins(t_shell *shell, int args, int *r)
{
  int	i;

  i = 0;
  if (!my_strcmp(shell->cur->av[0], "config"))
    {
      *r = launch_config(shell);
      i = 1;
    }
  else if (my_strcmp(shell->cur->av[0], "exit") == 0)
    {
      *r = check_exit(shell, args);
      i = 1;
    }
  else if (my_strcmp(shell->cur->av[0], "env") == 0)
    {
      if (args == 1)
        *r = disp_env();
      else
        my_print_err("env - invalid number of arguments\n");
      i = 1;
    }
  return (exec_builtins2(shell, args, r, i));
}
