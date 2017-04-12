/*
** env.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:59:59 2017 Nicolas Polomack
** Last update Thu Apr  6 09:11:07 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

void	mod_env(char ***ae, char *name, char *val, int l)
{
  free((*ae)[l]);
  (*ae)[l] = malloc(my_strlen(name) + my_strlen(val) + 2);
  (*ae)[l][0] = 0;
  (*ae)[l] = my_strcat(my_strcat(my_strcat((*ae)[l], name), "="), val);
}

int	set_env(char ***ae, char *name, char *value)
{
  int	i;
  int	j;

  i = -1;
  if (check_env_error(name))
    return (1);
  i = -1;
  if (*ae != NULL)
    while ((*ae)[++i])
      {
	j = -1;
	while (++j < my_strlen(name))
	  if ((*ae)[i][j] == name[j] && name[j + 1] == 0 &&
	      (*ae)[i][j + 1] == '=')
	    {
	      mod_env(ae, name, value, i);
	      return (0);
	    }
	  else if ((*ae)[i][j] != name[j])
	    break;
      }
  *ae = add_to_env(*ae, name, value);
  return (0);
}

int	unset_env(char ***ae, char **names)
{
  int	i[3];

  if ((*ae) == NULL)
    return (0);
  i[2] = 0;
  while (names[++(i[2])])
    {
      i[0] = -1;
      while ((*ae)[++(i[0])])
	{
	  i[1] = -1;
	  while (++(i[1]) < my_strlen(names[i[2]]))
	    if ((*ae)[i[0]][i[1]] == names[i[2]][i[1]] &&
		names[i[2]][i[1] + 1] == 0 &&
		(*ae)[i[0]][i[1] + 1] == '=')
	      {
		if (remove_env_entry(ae, i[0]))
		  return (1);
		break;
	      }
	    else if ((*ae)[i[0]][i[1]] != names[i[2]][i[1]])
	      break;
	  if (!((*ae)[(i[0])]))
	    return (0);
	}
    }
  return (0);
}

int	remove_env_entry(char ***ae, int l)
{
  int	i;
  char	**env;

  i = -1;
  while ((*ae)[++i] != NULL);
  if (i == 1)
    {
      free((*ae)[0]);
      free(*ae);
      (*ae) = NULL;
      return (0);
    }
  if ((env = malloc(sizeof(char *) * i)) == NULL)
    return (-1);
  i = -1;
  while (++i < l)
    env[i] = (*ae)[i];
  while ((*ae)[++i] != NULL)
    env[i - 1] = (*ae)[i];
  env[i - 1] = NULL;
  free((*ae)[l]);
  (*ae) = env;
  return (0);
}

char	**copy_env(char **ae)
{
  int	i;
  char	**env;

  i = -1;
  if (ae == NULL)
    return (NULL);
  while (ae[++i] != NULL);
  env = malloc(sizeof(char *) * (i + 1));
  i = -1;
  while (ae[++i] != NULL)
    env[i] = my_strdup(ae[i]);
  env[i] = NULL;
  return (env);
}
