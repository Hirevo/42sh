/*
** add_env_http.c for add_env_http in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon Apr 24 23:36:51 2017 Arthur Knoepflin
** Last update Tue Apr 25 11:30:45 2017 Arthur Knoepflin
*/

#include "server.h"
#include "my.h"

void	add_env_http(t_socket client, char **arg, char ***ae)
{
  char	*str;

  str = NULL;
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
