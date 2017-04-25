/*
** main.c for server in /home/arthur/test_sock/server
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Wed Dec 21 21:16:01 2016 Arthur Knoepflin
** Last update Tue Apr 25 00:04:36 2017 Arthur Knoepflin
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "server.h"
#include "my.h"

static int	init_client(fd_set *rdfs,
			    int actual,
			    t_socket sock,
			    t_socket *clients)
{
  int		i;

  i = 0;
  FD_ZERO(rdfs);
  FD_SET(STDIN_FILENO, rdfs);
  FD_SET(sock, rdfs);
  while (i < actual)
    {
      FD_SET(clients[i], rdfs);
      i += 1;
    }
  if (select(MAX_CLIENTS + 1, rdfs, NULL, NULL, NULL) == -1)
    {
      perror("select ");
      return (1);
    }
  return (0);
}

static void	clear_clients(t_socket *clients, int actual)
{
  int		i;

  i = 0;
  while (i < actual)
    {
      closesocket(clients[i]);
      i += 1;
    }
}

static int	core(t_socket sock, char **ae, int actual)
{
  int		i;
  int		stop;
  t_socket	clients[MAX_CLIENTS];
  fd_set	rdfs;

  stop = 0;
  while (!stop)
    {
      init_client(&rdfs, actual, sock, clients);
      if (FD_ISSET(STDIN_FILENO, &rdfs))
	stop = 1;
      else if (FD_ISSET(sock, &rdfs))
	new_client(clients, &actual, &rdfs, sock);
      else
	stop = client_talk(clients, &actual, &rdfs, &ae);
    }
  my_putstr("Fermeture du serveur\n");
  clear_clients(clients, actual);
  closesocket(sock);
}

int		main(int ac, char **av, char **ae)
{
  int		port;
  t_socket	sock;
  char		*p_nav;

  if ((p_nav = find_navigator(ae)) == NULL)
    {
      my_puterror("Aucun navigateur trouvé\n");
      return (84);
    }
  srand(getpid() * time(NULL));
  if ((port = init_connection(&sock)) == -1)
    return (84);
  my_putstr("Initialisation terminé\n");
  launch_nav(p_nav, port, ae);
  core(sock, ae, 0);
  return (0);
}
