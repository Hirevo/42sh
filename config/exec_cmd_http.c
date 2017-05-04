/*
** exec_cmd_http.c for exec_cmd_http in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed Apr 26 23:40:25 2017 Arthur Knoepflin
** Last update Thu May  4 17:34:28 2017 Arthur Knoepflin
*/

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "my.h"

char	*get_cmd_exc(char *cmd_path, char *cmd)
{
  char	*tmp;

  if (cmd_path && !my_strcmp(cmd_path, "emacs"))
    return (my_strdup(cmd));
  else
    {
      tmp = my_strcat("timeout 1 ", cmd);
      return (my_strcat(tmp, " 2>&1"));
    }
}

static int	execute_http(t_socket client, char *cmd, char **cmd_p)
{
  char		*cmd_exc;
  int		sauv;

  sauv = 8;
  if (dup2(1, sauv) == -1)
    return (1);
  cmd_exc = get_cmd_exc(cmd_p[0], cmd);
  if (dup2(client, 1) == -1)
    return (1);
  system(cmd_exc);
  dup2(sauv, 1);
}

static int	change_dir_http(t_socket client, char **cmd_p)
{
  if (nb_args(cmd_p) >= 2)
    {
      if (chdir(cmd_p[1]) == -1)
	write_client(client, strerror(errno));
      else
	{
	  write_client(client, "Change to ");
	  write_client(client, cmd_p[1]);
	}
    }
  else
    write_client(client, "Error: precise a folder");
}

int	exec_cmd_http(t_socket client, char **arg, char ***ae)
{
  char	*cmd;
  char	**cmd_p;

  if ((cmd = malloc(sizeof(char) * (my_strlen(arg[3]) + 1))) == NULL)
    return (1);
  urldecode(arg[3], cmd);
  if ((cmd_p = my_split_char(cmd, ' ')) == NULL)
    return (1);
  write_client(client, BASE_RESP);
  if (!my_strcmp(cmd_p[0], "cd"))
    change_dir_http(client, cmd_p);
  else
    execute_http(client, cmd, cmd_p);
  return (0);
}
