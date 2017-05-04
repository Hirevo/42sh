/*
** add_env_http.c for add_env_http in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon Apr 24 23:36:51 2017 Arthur Knoepflin
** Last update Wed Apr 26 23:23:47 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "server.h"
#include "my.h"

void	add_env_http(t_socket client, char **arg, char ***ae)
{
  char	*str;

  str = NULL;
  if (indexof(*ae, arg[3]) != -1)
    {
      write_client(client, ERROR_RESP);
      return ;
    }
  if (nb_args(arg) == 6)
    {
      str = my_strcat("", arg[3]);
      str = my_strcat(str, "=");
      str = my_strcat(str, arg[5]);
    }
  else if (nb_args(arg) == 5)
    {
      str = my_strcat("", arg[3]);
      str = my_strcat(str, "=");
    }
  *ae = add_to_chardouble(str, *ae);
  write_client(client, BASE_RESP);
  write_client(client, "add_env_ok");
}

void	del_env_http(t_socket client, char **arg, char ***ae)
{
  *ae = del_to_chardouble(arg[3], *ae);
  write_client(client, BASE_RESP);
  write_client(client, "del_env_ok");
}

void	update_env_http(t_socket client, char **arg, char ***ae)
{
  int	idx;
  char	*decode;
  char	*new;

  new = my_strcat(arg[3], "=");
  if (nb_args(arg) == 6)
    {
      if ((decode = malloc(sizeof(char) *
			   (my_strlen(arg[5]) + 1))) == NULL)
	return ;
      urldecode(arg[5], decode);
      new = my_strcat(new, decode);
    }
  if ((idx = indexof(*ae, arg[3])) != -1)
    (*ae)[idx] = new;
  write_client(client, BASE_RESP);
  write_client(client, "update_env_ok");
}
