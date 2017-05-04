/*
** path.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:46:13 2017 Nicolas Polomack
** Last update Sun Jan 22 01:17:02 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

char	*cat_path(char **path, char *final, int i)
{
  char	*str;
  char	*dir;

  if (i == -1 || i == -2)
    dir = my_strdup((i == -2) ? "/bin" : "/usr/bin");
  else if (i >= 0)
    dir = path[i];
  else
    return (NULL);
  str = malloc(my_strlen(dir) + my_strlen(final) + 2);
  *str = 0;
  str = my_strcat(str, dir);
  if (dir[my_strlen(dir)] != '/')
    str[my_strlen(dir)] = '/';
  str[my_strlen(dir) + 1] = 0;
  str = my_strcat(str, final);
  if (i < 0)
    free(dir);
  return (str);
}

int	is_path(char *str)
{
  int	i;

  i = -1;
  while (str[++i] != 0)
    if (str[i] == '/')
      return (1);
  return (0);
}

char	**init_path(char **ae)
{
  int	i;
  int	arg;
  char	**path;
  char	*str;

  if (ae == NULL)
    return (NULL);
  i = -1;
  str = NULL;
  while (ae[++i] != NULL)
    if (ae[i][0] == 'P' && ae[i][1] == 'A' && ae[i][2] == 'T' &&
        ae[i][3] == 'H' && ae[i][4] == '=')
      str = my_strdup((ae[i]) + 5);
  if (str == NULL ||
      (path = malloc(sizeof(char *) * (count_entries(str) + 2))) == NULL)
    return (NULL);
  i = 0;
  arg = 0;
  while ((i = get_next_entry(str, &(path[arg++]), i)) != -2)
    if (i == -1)
      return (NULL);
  path[arg] = NULL;
  free(str);
  return (path);
}

void		set_path(t_shell *shell, char *path)
{
  int		i;
  int		obj;
  char		*name;
  char		*entry;

  i = -1;
  obj = my_strlen_spe(path, '=');
  if ((name = malloc(obj + 1)) == NULL)
    return ;
  while (++i < obj)
    name[i] = path[i];
  name[i] = 0;
  i = obj + 1;
  obj = my_strlen_spe(path + i , '\0');
  if ((entry = malloc(obj + 1)) == NULL)
    return ;
  obj = i;
  i = -1;
  while ((path + obj)[++i] != 0)
    entry[i] = (path + obj)[i];
  entry[i] = 0;
  set_env(&(shell->env), name, entry);
  free(name);
  free(entry);
}

void	parse_path(t_shell *shell)
{
  int	fd;
  char	*path;

  if ((shell->home == NULL) || (path = malloc(512)) == NULL)
    return ;
  path[0] = 0;
  path = my_strcat(path, shell->home);
  if (shell->home[my_strlen(shell->home)] != '/')
    path[my_strlen(shell->home)] = '/';
  path[my_strlen(shell->home) + 1] = 0;
  path = my_strcat(path, ".myshrc");
  if ((fd = open(path, O_RDONLY)) == -1)
    return ;
  free(path);
  while ((path = get_next_line(fd)) != NULL)
    {
      if (is_valid_path(path))
        set_path(shell, path);
      free(path);
    }
  close(fd);
}
