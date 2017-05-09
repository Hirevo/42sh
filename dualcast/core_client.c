/*
** core_client.c for core_client in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon May  8 12:13:20 2017 Arthur Knoepflin
** Last update Tue May  9 18:10:55 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "get_next_line.h"
#include "server.h"
#include "my.h"

static int		init_select_dc(t_socket *com, fd_set *rdfs)
{
  FD_ZERO(rdfs);
  FD_SET(STDIN_FILENO, rdfs);
  FD_SET(*com, rdfs);
  if ((select(*com + 1, rdfs, NULL, NULL, NULL)) == -1)
    return (1);
  return (0);
}

static void	treat_serv_resp(t_socket sock,
				char *str,
				char **prompt,
				int *nb_char)
{
  char		*tmp;

  if (str && my_strcmp(str, "OK"))
    {
      my_printf("\n%s", str);
      tmp = my_strcatdup("cmd:", str);
      write_socket(sock, tmp);
      free(tmp);
      *prompt = my_strdup("(\033[32;1mDualCast\033[0m) $> ");
      *nb_char = my_strlen(*prompt);
      my_putstr(*prompt);
    }
}

static int	read_term(t_socket sock, char **prompt, int *nb_char)
{
  char		c;

  c = getch_c();
  if (c == 13)
    {
      *prompt = my_strdup("(\033[32;1mDualCast\033[0m) $> ");
      *nb_char = my_strlen(*prompt);
      my_printf("\n%s", *prompt);
    }
  if (c == 3)
    {
      my_putchar('\n');
      return (1);
    }
  if (c >= 32 && c <= 126)
    add_char_dc(prompt, c, nb_char);
  else if (c == 127)
    del_last_char(prompt, nb_char);
  del_prompt(*nb_char);
  my_printf("\r%s", *prompt);
  send_char(sock, c);
  return (0);
}

static int	read_sock(t_socket sock, char **prompt, int *nb_char)
{
  char		*buf;
  int		len;

  len = read_socket(sock, &buf);
  if (len == 0)
    {
      my_printf("Vous avez été déconnecté\n");
      return (1);
    }
  else
    treat_serv_resp(sock, buf, prompt, nb_char);
  free(buf);
  return (0);
}

int			core_client_dc(t_socket com)
{
  int			stop;
  fd_set		rdfs;
  char			*prompt;
  struct termios	orig_termios;
  int			nb_char;

  stop = 0;
  prompt = my_strdup("(\033[32;1mDualCast\033[0m) $> ");
  nb_char = my_strlen(prompt);
  my_putstr(prompt);
  while (!stop)
    {
      set_conio_terminal_mode(&orig_termios);
      stop = init_select_dc(&com, &rdfs);
      reset_terminal_mode(&orig_termios);
      if (FD_ISSET(STDIN_FILENO, &rdfs))
	stop = read_term(com, &prompt, &nb_char);
      else if (FD_ISSET(com, &rdfs))
	stop = read_sock(com, &prompt, &nb_char);
    }
}
