/*
** send_info.c for send_info in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May  2 18:21:00 2017 Arthur Knoepflin
** Last update Thu May  4 22:08:37 2017 Arthur Knoepflin
*/

#include "server.h"
#include "my.h"

static char	*get_resp(t_info_pc *info)
{
  char		*ret;

  ret = my_strcatdup("{\"hostname\" : \"", info->hostname);
  ret = my_strcatdup(ret, "\", \"os\" : \"");
  ret = my_strcatdup(ret, info->os);
  ret = my_strcatdup(ret, "\", \"platform\" : \"");
  ret = my_strcatdup(ret, info->plateforme);
  ret = my_strcatdup(ret, "\", \"version\" : \"");
  ret = my_strcatdup(ret, info->version);
  ret = my_strcatdup(ret, "\", \"memory_total\" : ");
  ret = my_strcatdup(ret, int_toc(info->mem_total));
  ret = my_strcatdup(ret, ", \"memory_available\" : ");
  ret = my_strcatdup(ret, int_toc(info->mem_available));
  ret = my_strcatdup(ret, ", \"process\" : \"");
  ret = my_strcatdup(ret, info->proco);
  return (my_strcatdup(ret, "\"}"));
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
