/*
** bufferize.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Jan  9 10:55:14 2017 Nicolas Polomack
** Last update Fri May  5 06:48:41 2017 Nicolas Polomack
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
  return (!my_strcmp(str, "env") || !my_strcmp(str, "alias") ||
	  !my_strcmp(str, "setenv") || !my_strcmp(str, "exit") ||
	  !my_strcmp(str, "unsetenv") || !my_strcmp(str, "cd") ||
	  !my_strcmp(str, "config") || !my_strcmp(str, "echo"));
}
