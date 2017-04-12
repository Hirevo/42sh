/*
** bufferize.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Jan  9 10:55:14 2017 Nicolas Polomack
** Last update Sun Mar 26 19:48:46 2017 Nicolas Polomack
*/

#include <sys/stat.h>
#include "my.h"

int	is_redirect(char *str)
{
  return (my_strcmp(str, ">") == 0 || my_strcmp(str, "<") == 0 ||
	  my_strcmp(str, ">>") == 0 || my_strcmp(str, "<<") == 0);
}


int	is_right_redirect(char *str)
{
  return (my_strcmp(str, ">") == 0 || my_strcmp(str, ">>") == 0);
}

int	is_left_redirect(char *str)
{
  return (my_strcmp(str, "<") == 0 || my_strcmp(str, "<<") == 0);
}

int		is_dir(char *name)
{
  struct stat	stats;

  if (stat(name, &stats) == -1)
    return (0);
  return (S_ISDIR(stats.st_mode) ? 1 : 0);
}

int	is_builtin(char *str)
{
  return (my_strcmp(str, "env") == 0 || my_strcmp(str, "alias") == 0 ||
	  my_strcmp(str, "setenv") == 0 || my_strcmp(str, "exit") == 0 ||
	  my_strcmp(str, "unsetenv") == 0 || my_strcmp(str, "cd") == 0);
}
