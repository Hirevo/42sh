/*
** exit.c for exit_config in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May 16 10:50:36 2017 Arthur Knoepflin
** Last update Wed May 17 11:21:42 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "shell.h"
#include "server.h"
#include "my.h"

void	exit_config(t_socket client, t_config *config, char **arg)
{
  char	*str;

  my_putstr("Configuration terminé\n");
  str = my_strcatdup(BASE_RESP, "quit");
  write_client(client, str);
  free(str);
}
