/*
** exec_cmd_http.c for exec_cmd_http in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed Apr 26 23:40:25 2017 Arthur Knoepflin
** Last update Wed Apr 26 23:46:26 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "server.h"
#include "my.h"

int	exec_cmd_http(t_socket client, char **arg, char ***ae)
{
  char	*cmd;

  if ((cmd = malloc(sizeof(char) * (my_strlen(arg[3]) + 1))) == NULL)
    return (1);
  urldecode(arg[3], cmd);
  printf("cmd : %s\n", cmd);
  return (0);
}
