/*
** response.c for response in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sat Apr 22 14:33:57 2017 Arthur Knoepflin
** Last update Tue Apr 25 23:56:12 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "my.h"

static int	strlen_space(char *str)
{
  int		i;

  str += 4;
  i = 0;
  while (str && str[i] && str[i] != ' ')
    i += 1;
  return (i - 6);
}

static char	*get_arg(char *head)
{
  char		**resp;
  char		**req;
  int		i;

  resp = my_split(head, "\r\n\r\n");
  if (resp)
    {
      req = my_split(resp[0], "\r\n");
      if (req && !my_strncmp(req[0], "GET", 3))
	{
	  i = 0;
	  while (req[0][i] && req[0][i] != '?')
	    i += 1;
	  i += 1;
	  return (my_strndup(req[0] + i, strlen_space(req[0])));
	}
    }
  return (NULL);
}

static int	parse_arg(t_socket client, char **arg, char ***ae)
{
  if (!my_strcmp(arg[1], "quit"))
    {
      my_putstr("Configuration terminé\n");
      write_client(client, my_strcat(BASE_RESP, "quit"));
      return (1);
    }
  else if (!my_strcmp(arg[1], "get_env"))
    send_env(client, *ae);
  else if (!my_strcmp(arg[1], "add_env") && nb_args(arg) >= 5)
    add_env_http(client, arg, ae);
  else if (!my_strcmp(arg[1], "update_env") && nb_args(arg) >= 5)
    update_env_http(client, arg, ae);
  else if (!my_strcmp(arg[1], "del_env") && nb_args(arg) == 4)
    del_env_http(client, arg, ae);
  else
    write_client(client, BASE_RESP);
  return (0);
}

int	response(t_socket client, char *buf, char ***ae)
{
  char	*file;
  char	*r_arg;
  char	**arg;

  if ((file = get_file_http(buf)) == NULL)
    return (1);
  if (!my_strncmp(file + 1, MAGIC, my_strlen(MAGIC)))
    {
      if ((r_arg = get_arg(buf)) && (arg = my_split_mulchar(r_arg, "&=")))
	  if (!my_strcmp(arg[0], "arg"))
	    return (parse_arg(client, arg, ae));
    }
  else
    send_file_http(client, my_strcat(PATH_DOC, get_file_http(buf)));
  return (0);
}
