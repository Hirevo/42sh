/*
** prompt.c for prompt in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May  4 23:33:54 2017 Arthur Knoepflin
** Last update Fri May  5 00:52:17 2017 Arthur Knoepflin
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "prompt.h"
#include "get_next_line.h"
#include "shell.h"

char	*get_hostname(void)
{
  char	*ret;
  int	fd;

  if ((fd = open("/etc/hostname", O_RDONLY)) == -1)
    return (NULL);
  ret = get_next_line(fd);
  close(fd);
  return (ret);
}

static void	get_tab_prompt(void (*tab_prompt[6])(t_shell *))
{
  tab_prompt[0] = &turbosh_prompt;
  tab_prompt[1] = &bash_prompt;
  tab_prompt[2] = &tcsh_prompt;
  tab_prompt[3] = &minimalist_prompt;
}

void	print_prompt(t_shell *shell)
{
  void	(*tab_prompt[6])(t_shell *);

  get_tab_prompt(tab_prompt);
  if (shell->prompt >= 0 && shell->prompt < 6)
    tab_prompt[shell->prompt](shell);
  else
    tab_prompt[0](shell);
}
