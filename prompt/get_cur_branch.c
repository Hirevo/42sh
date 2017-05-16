/*
** show_cur_branch.c for cur_branch in /home/leuzzi_l/Leuzzi/PSU/PSU_2016_42sh
** 
** Made by ludovic leuzzi
** Login   <leuzzi_l@epitech.net>
** 
** Started on  Fri May 12 18:11:29 2017 ludovic leuzzi
** Last update Tue May 16 12:50:17 2017 Arthur Knoepflin
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
  while (j != 2)
    {
      if (tmp[i] == '/')
	j++;
      i++;
    }
  if ((res = malloc(sizeof(char) * ((my_strlen(tmp) - i) + 1))) == NULL)
    return (NULL);
  while (tmp[i])
    res[k++] = tmp[i++];
  res[k] = '\0';
  free(tmp);
  return (res);
}

static char	*find_branch(char *path)
{
  int		i;
  int		fd;
  char		*tmp;

  i = 0;
  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  tmp = get_next_line(fd);
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
