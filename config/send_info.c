/*
** send_info.c for send_info in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May  2 18:21:00 2017 Arthur Knoepflin
** Last update Tue May  2 22:36:41 2017 Arthur Knoepflin
*/

#include "server.h"
#include "my.h"

static char	*get_resp(t_info_pc *info)
{
  char		*ret;

  ret = my_strcat("{\"hostname\" : \"", info->hostname);
  ret = my_strcat(ret, "\", \"os\" : \"");
  ret = my_strcat(ret, info->os);
  ret = my_strcat(ret, "\", \"platform\" : \"");
  ret = my_strcat(ret, info->plateforme);
  ret = my_strcat(ret, "\", \"version\" : \"");
  ret = my_strcat(ret, info->version);
  ret = my_strcat(ret, "\", \"memory_total\" : ");
  ret = my_strcat(ret, int_toc(info->mem_total));
  ret = my_strcat(ret, ", \"memory_available\" : ");
  ret = my_strcat(ret, int_toc(info->mem_available));
  ret = my_strcat(ret, ", \"process\" : \"");
  ret = my_strcat(ret, info->proco);
  return (my_strcat(ret, "\"}"));
}

void		send_info(t_socket client)
{
  char		*resp;
  t_info_pc	*info;

  if ((info = get_info()) == NULL)
    {
      write_client(client, ERROR_RESP);
      return ;
    }
  write_client(client, HEAD_RESP);
  write_client(client, "Content-type: application/json\r\n\r\n");
  resp = get_resp(info);
  write_client(client, resp);
}
