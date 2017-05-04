/*
** home.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 11:04:03 2017 Nicolas Polomack
** Last update Sun Jan 22 01:16:40 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

char	*get_home(char **env)
{
  int	i;

  i = -1;
  if (env == NULL)
    return (NULL);
  while (env[++i] != NULL)
    if (env[i][0] == 'H' && env[i][1] == 'O' && env[i][2] == 'M' &&
        env[i][3] == 'E' && env[i][4] == '=' && env[i][5] != 0)
      return (my_strdup(env[i] + 5));
  return (NULL);
}

char	*detect_home(char *temp, char *home)
{
  int	i;
  int	j;

  i = 0;
  if (home != NULL)
    {
      while (temp[i] == home[i] && temp[i] != 0)
        i += 1;
      if (home[i] == 0)
        {
          temp[0] = '~';
          i -= (home[i - 1] == '/');
          j = 1;
          while (temp[i] != 0)
            {
              temp[j] = temp[i];
              i += 1;
              j += 1;
            }
          temp[j] = 0;
        }
    }
  return (temp);
}

char	*get_current(char *current, char *home)
{
  int   i;
  char  *temp;

  i = -1;
  if ((temp = malloc(512)) == NULL)
    return (NULL);
  temp[0] = 0;
  current[0] = 0;
  current = my_strcat(current, "\e[32m");
  if ((temp = getcwd(temp, 256)) == NULL)
    return (NULL);
  if (home && my_strcmp(home, "/"))
  temp = detect_home(temp, home);
  current = my_strcat(my_strcat(current, temp), "\e[0m ");
  free(temp);
  return (current);
}
