/*
** core_server.c for core_server in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sat May  6 22:51:45 2017 Arthur Knoepflin
** Last update Mon May  8 18:12:24 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#include "server.h"
#include "my.h"

static int	init_client_dc(fd_set *rdfs,
			       t_socket *sock,
			       t_socket *client)
{
  FD_ZERO(rdfs);
  FD_SET(STDIN_FILENO, rdfs);
  FD_SET(*sock, rdfs);
  FD_SET(*client, rdfs);
  if (select(*client + 1, rdfs, NULL, NULL, NULL) == -1)
    {
      perror("select ");
      return (3);
    }
  return (0);
}

int		new_client_dc(t_socket sock)
{
  t_sockaddr_in	csin;
  socklen_t	sinsize;
  t_socket	csock;

  sinsize = sizeof(csin);
  if ((csock = accept(sock, (t_sockaddr *)&csin, &sinsize)) == SOCKET_ERROR)
    {
      perror("");
      return (1);
    }
  close(csock);
}

static int	client_talk_dc(t_socket client, fd_set *rdfs)
{
  int		ret;
  int		len;
  char		*buf;

  if (FD_ISSET(client, rdfs))
    {
      len = read_socket(client, &buf);
      if (len == 0)
	{
	  close(client);
	  return (1);
	}
      else
	{
	  write_socket(client, "OK");
	  printf("%s\n", buf);
	}
    }
  return (0);
}

int	core_server_dc(t_socket sock, t_socket client, fd_set *rdfs)
{
  int	stop;

  stop = 0;
  my_putstr("(\033[32;1mDualCast\033[0m) $> ");
  while (!stop)
    {
      stop = init_client_dc(rdfs, &sock, &client);
      if (FD_ISSET(STDIN_FILENO, rdfs) && !stop)
	stop = 2;
      else if (FD_ISSET(sock, rdfs) && !stop)
	new_client_dc(sock);
      else if (!stop)
	stop = client_talk_dc(client, rdfs);
    }
  if (FD_ISSET(STDIN_FILENO, rdfs))
    free(get_next_line(0));
}
