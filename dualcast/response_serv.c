/*
** response_serv.c for response_serv in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May  9 11:31:56 2017 Arthur Knoepflin
** Last update Tue May  9 18:45:45 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "shell.h"
#include "my.h"

static void	print_cmd(char *buf, char **prompt, int *nb_char)
{
  my_printf("\n%s", buf + 4);
  *prompt = my_strdup("(\033[32;1mDualCast\033[0m) $> ");
  *nb_char = my_strlen(*prompt);
  my_printf("%s", *prompt);
}

int	response_serv(t_socket sock,
		      char *buf,
		      char **prompt,
		      int *nb_char)
{
  if (!my_strncmp(buf, "char:", 5))
    prompt_serv(sock, buf[5], prompt, nb_char);
  if (!my_strncmp(buf, "cmd:", 4))
    print_cmd(buf, prompt, nb_char);
  free(buf);
}
