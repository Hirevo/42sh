/*
** get_env.c for get_env in /home/arthur/delivery/PSU/PSU_2016_minishell1
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Wed Jan  4 14:16:49 2017 Arthur Knoepflin
** Last update Sat Apr 22 18:25:03 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "server.h"
#include "my.h"

int	get_len(char *str)
{
  int	i;

  i = 0;
  while (str[i] && str[i] != '=')
    i += 1;
  if (i != 0)
    i += 1;
  return (i);
}

char	*get_env(char **env, char *str)
{
  int	i;
  char	*ret;

  i = 0;
  while (env && env[i])
    {
      if (my_strncmp(env[i], str, my_strlen(str)) == 0 &&
	  env[i][my_strlen(str)] == '=')
	{
	  ret = my_strdup(env[i] + get_len(env[i]));
	  return (ret);
	}
      i += 1;
    }
  return (NULL);
}
