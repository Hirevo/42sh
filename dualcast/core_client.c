/*
** core_client.c for core_client in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon May  8 12:13:20 2017 Arthur Knoepflin
** Last update Tue May  9 09:47:39 2017 Arthur Knoepflin
*/

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

static int	read_term(t_socket sock, char **prompt)
{
  char		c;

  c = getch_c();
  if (c == 3)
    return (1);
  if (c >= 32 && c <= 126)
    add_char_dc(prompt, c);
  else if (c == 127)
    del_last_char(prompt);
  my_putstr("\r");
  my_putstr(*prompt);
  return (0);
}

static int	read_sock(t_socket sock)
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
    printf("%s\n", buf);
  return (0);
}

int			core_client_dc(t_socket com)
{
  int			stop;
  fd_set		rdfs;
  char			*prompt;
  struct termios	orig_termios;

  stop = 0;
  prompt = my_strdup("(\033[32;1mDualCast\033[0m) $> ");
  my_putstr(prompt);
  while (!stop)
    {
      set_conio_terminal_mode(&orig_termios);
      stop = init_select_dc(&com, &rdfs);
      reset_terminal_mode(&orig_termios);
      if (FD_ISSET(STDIN_FILENO, &rdfs))
	stop = read_term(com, &prompt);
      else if (FD_ISSET(com, &rdfs))
	stop = read_sock(com);
    }
}
