/*
** env2.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 11:01:50 2017 Nicolas Polomack
** Last update Sun Jan 22 01:16:09 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

int	disp_env(char **ae)
{
  int	i;

  if (ae == NULL)
    return (0);
  i = -1;
  while (ae[++i] != NULL)
    my_printf("%s\n", ae[i]);
  return (0);
}

int	check_env_error(char *name)
{
  if (name[0] == 0 || ((name[0] < 'a' || name[0] > 'z') &&
                       (name[0] < 'A' || name[0] > 'Z')))
    return (my_print_err("setenv: Variable name must begin with a letter.\n"));
  if (!is_char_alpha(name))
    return (my_print_err("setenv: Variable name must") - 1 +
	    my_print_err(" contain alphanumeric characters.\n"));
  return (0);
}

char	**add_to_env(char **ae, char *name, char *val)
{
  char	**env;
  int	i;

  i = -1;
  if (ae == NULL)
    i = 0;
  else
    while (ae[++i] != NULL);
  env = malloc(sizeof(char *) * (i + 2));
  i = 0;
  if (ae != NULL)
    while (ae[i] != NULL)
      {
        env[i] = ae[i];
        i += 1;
      }
  env[i] = malloc(my_strlen(name) + my_strlen(val) + 2);
  env[i][0] = 0;
  env[i] = my_strcat(my_strcat(my_strcat(env[i], name), "="), val);
  env[i + 1] = NULL;
  free(ae);
  return (env);
}
