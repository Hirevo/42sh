/*
** show_cur_branch.c for cur_branch in /home/leuzzi_l/Leuzzi/PSU/PSU_2016_42sh
** 
** Made by ludovic leuzzi
** Login   <leuzzi_l@epitech.net>
** 
** Started on  Fri May 12 18:11:29 2017 ludovic leuzzi
** Last update Tue May 16 13:32:06 2017 Arthur Knoepflin
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "my.h"

static char	*cut_path(char *tmp)
{
  int		i;
  int		j;
  int		k;
  char		*res;

  i = 0;
  j = 0;
  k = 0;
  while (tmp && tmp[i] && j != 2)
    {
      if (tmp && tmp[i] == '/')
	j++;
      i++;
    }
  if (j != 2)
    return (NULL);
  if ((res = malloc(sizeof(char) * ((my_strlen(tmp) - i) + 1))) == NULL)
    return (NULL);
  while (tmp[i])
    res[k++] = tmp[i++];
  res[k] = '\0';
  free(tmp);
  return (res);
}

static int	is_sha1(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (!((str[i] >= '0' && str[i] <= '9') ||
	    (str[i] >= 'a' && str[i] <= 'f')))
	return (0);
      i += 1;
    }
  if (i != 40)
    return (0);
  return (1);
}

static char	*find_branch(char *path)
{
  int		i;
  int		fd;
  char		*tmp;

  i = 0;
  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  if ((tmp = get_next_line(fd)) == NULL)
    {
      close(fd);
      return (NULL);
    }
  close(fd);
  if (is_sha1(tmp))
    return (my_strndup(tmp, 7));
  return (cut_path(tmp));
}

char	*show_cur_branch()
{
  char	*branch;
  char	*path;

  path = my_strdup("./.git");
  while (path != NULL)
    {
      if ((access(path, F_OK) == -1))
	{
	  if ((access("./home", F_OK) == 1))
	    path = NULL;
	  path = my_strcatdup("../", path);
	}
      else
	{
	  path = my_strcatdup(path, "/HEAD");
	  if ((branch = find_branch(path)) == NULL)
	    {
	      free(path);
	      return (NULL);
	    }
	  free(path);
	  return (branch);
	}
    }
  return (NULL);
}
