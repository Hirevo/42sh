/*
** get_info_pc.c for get_info_pc in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May  2 17:20:13 2017 Arthur Knoepflin
** Last update Thu May  4 19:23:59 2017 Arthur Knoepflin
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "server.h"
#include "get_next_line.h"

int	parse_version(t_info_pc *ret)
{
  char	*str;
  int	fd;

  if ((fd = open("/proc/version", O_RDONLY)) == -1)
    return (1);
  get_next_line(-1);
  str = get_next_line(fd);
  ret->plateforme = my_strdup_until_x(str, ' ', 0);
  ret->version = my_strdup_until_x(str +
				   my_strlen_until_x(str, ' ', 1) + 1, ' ', 1);
  ret->os = my_strdup_until_x(str +
			      my_strlen_until_x(str, ' ', 13) + 1, ' ', 2);
  close(fd);
  if ((fd = open("/etc/hostname", O_RDONLY)) == -1)
    return (1);
  get_next_line(-1);
  ret->hostname = get_next_line(fd);
  close(fd);
  return (0);
}

int	parse_ram(t_info_pc *ret)
{
  char	*str;
  int	fd;
  int	i;

  if ((fd = open("/proc/meminfo", O_RDONLY)) == -1)
    return (1);
  while ((str = get_next_line(fd)))
    {
      if (!my_strncmp(str, "MemTotal:", 9))
	{
	  i = 9;
	  while (str[i] && !(str[i] >= '0' && str[i] <= '9'))
	    i += 1;
	  ret->mem_total = my_getnbr(str + i);
	}
      if (!my_strncmp(str, "MemAvailable:", 13))
	{
	  i = 13;
	  while (str[i] && !(str[i] >= '0' && str[i] <= '9'))
	    i += 1;
	  ret->mem_available = my_getnbr(str + i);
	}
    }
  close(fd);
  return (0);
}

int	parse_proco(t_info_pc *ret)
{
  char	*str;
  int	fd;
  int	i;

  if ((fd = open("/proc/cpuinfo", O_RDONLY)) == -1)
    return (1);
  while ((str = get_next_line(fd)))
    if (!my_strncmp(str, "model name", 10))
      {
	i = 10;
	while (str[i] && str[i] != ':')
	  i += 1;
	i += 2;
	ret->proco = my_strdup(str + i);
      }
  close(fd);
  return (0);
}

t_info_pc	*get_info(void)
{
  t_info_pc	*ret;

  if ((ret = malloc(sizeof(t_info_pc))) == NULL)
    return (NULL);
  my_memset(ret, 0, sizeof(t_info_pc));
  if (parse_version(ret))
    return (NULL);
  if (parse_ram(ret))
    return (NULL);
  if (parse_proco(ret))
    return (NULL);
  return (ret);
}
