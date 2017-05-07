/*
** bufferize.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Jan  9 10:55:14 2017 Nicolas Polomack
** Last update Sun May  7 22:23:50 2017 Nicolas Polomack
*/

#include <sys/stat.h>
#include "my.h"

int	is_right_redirect(char *str)
{
  return (my_strcmp(str, ">") == 0 || my_strcmp(str, ">>") == 0);
}

int	is_left_redirect(char *str)
{
  return (my_strcmp(str, "<") == 0 || my_strcmp(str, "<<") == 0);
}

int	is_builtin(char *str)
{
  return (!my_strcmp(str, "env") || !my_strcmp(str, "alias") ||
	  !my_strcmp(str, "setenv") || !my_strcmp(str, "exit") ||
	  !my_strcmp(str, "unsetenv") || !my_strcmp(str, "cd") ||
	  !my_strcmp(str, "config") || !my_strcmp(str, "echo") ||
	  !my_strcmp(str, "unalias"));
}
