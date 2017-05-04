/*
** navigator.c for navigator in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sat Apr 22 15:20:13 2017 Arthur Knoepflin
** Last update Thu May  4 21:35:55 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "server.h"
#include "my.h"

static char	**get_path(char **ae)
{
  char		*tmp;
  char		**ret;

  if ((ret = malloc(sizeof(char *) * 3)) == NULL)
    return (NULL);
  ret[2] = NULL;
  ret[0] = my_strdup("/bin");
  ret[1] = my_strdup("/usr/bin");
  if (!ae)
    return (ret);
  if ((tmp = get_env(ae, "PATH")) == NULL)
    return (ret);
  return (my_split(tmp, ":"));
}

static char	*test_access(char *tmp)
{
  char		*ret;

  ret = my_strcatdup(tmp, CHROME);
  if (access(ret, X_OK) == 0)
    return (ret);
  free(ret);
  ret = my_strcatdup(tmp, FIREFOX);
  if (access(ret, X_OK) == 0)
    return (ret);
  free(ret);
  return (NULL);
}

char	*find_navigator(char **ae)
{
  char	*tmp;
  char	*ret;
  char	**path;
  int	i;

  if ((path = get_path(ae)) == NULL)
    return (NULL);
  i = 0;
  while (path[i])
    {
      if (path[i][my_strlen(path[i]) - 1] != '/')
      	tmp = my_strcatdup(path[i], "/");
      else
      	tmp = my_strdup(path[i]);
      if ((ret = test_access(tmp)) != NULL)
	return (ret);
      free(tmp);
      i += 1;
    }
  return (NULL);
}

static int	dup_child(void)
{
  int		fd;

  if ((fd = open("/dev/null", O_RDONLY)) == -1)
    return (1);
  dup2(fd, 1);
  dup2(fd, 2);
  close(fd);
}

int	launch_nav(char *path, int port, char **ae)
{
  int	pid;
  char	**argv;

  if ((argv = malloc(sizeof(char *) * 3)) == NULL)
    return (1);
  argv[2] = NULL;
  argv[0] = path;
  argv[1] = my_strdup(PATH_WEB);
  argv[1] = my_strcatdup(argv[1], int_toc(port));
  if ((pid = fork()) == 0)
    {
      dup_child();
      execve(path, argv, ae);
      exit(0);
    }
  return (0);
}
