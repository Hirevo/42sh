/*
** prompt_serv.c for prompt_serv in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May  9 13:03:28 2017 Arthur Knoepflin
** Last update Tue May  9 20:29:25 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "server.h"
#include "shell.h"
#include "my.h"

static void	treat_client_resp(char *str, char **prompt, int *nb_char)
{
  if (str)
    {
      my_printf("\r%s", str + 4);
      free(str);
    }
}

static void	exc_cmd(t_socket sock, char **str, int *nb_char)
{
  char		*buf;
  int		sauv;
  int		sauv2;
  t_shell	shell;

  init_shell(&shell, NULL);
  shell.line = my_strdup(*str + 25);
  sauv = 8;
  sauv = 9;
  if (dup2(1, sauv) == -1)
    return ;
  if (dup2(2, sauv2) == -1)
    return ;
  if (dup2(sock, 1) == -1)
    return ;
  if (dup2(sock, 2) == -1)
    return ;
  exec_line(&shell, 0);
  dup2(sauv, 1);
  dup2(sauv2, 2);
}

void	prompt_serv(t_socket sock,
		    char c,
		    char **prompt,
		    int *nb_char)
{
  if (c == 13)
    {
      exc_cmd(sock, prompt, nb_char);
      *prompt = my_strdup("(\033[32;1mDualCast\033[0m) $> ");
      *nb_char = my_strlen(*prompt);
      my_printf("\n%s", *prompt);
      return ;
    }
  if (c >= 32 && c <= 126)
    add_char_dc(prompt, c, nb_char);
  else if (c == 127)
    del_last_char(prompt, nb_char);
  del_prompt(*nb_char);
  my_printf("\r%s", *prompt);
  write_client(sock, "OK");
  return ;
}
