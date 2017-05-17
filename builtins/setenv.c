/*
** setenv.c for setenv in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May 16 02:09:11 2017 Arthur Knoepflin
** Last update Wed May 17 09:49:10 2017 Arthur Knoepflin
*/

#include "shell.h"
#include "my.h"

int	setenv_b(t_shell *shell, int args)
{
  int	r;

  r = 0;
  if (args == 3 && my_strcmp(shell->cur->av[0], "setenv") == 0)
    r = set_env(shell->cur->av[1], shell->cur->av[2]);
  else if (args == 1 && my_strcmp(shell->cur->av[0], "setenv") == 0)
    r = disp_env();
  else if (args == 2 && my_strcmp(shell->cur->av[0], "setenv") == 0)
    r = set_env(shell->cur->av[1], "");
  /* else if (args == 1 && my_strcmp(shell->cur->av[0], "unsetenv") == 0) */
  /*   r = my_print_err("unsetenv: Too few arguments.\n"); */
  /* else if (my_strcmp(shell->cur->av[0], "unsetenv") == 0) */
  /*   r = unset_env(shell->cur->av); */
  else
    r = my_print_err(shell->cur->av[0]) +
      my_print_err(": Too many arguments.\n") - 1;
  reload_shell(shell);
  return (r);
}
