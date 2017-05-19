/*
** stars.c for stars in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May 19 09:59:04 2017 Arthur Knoepflin
** Last update Fri May 19 11:34:01 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <stdio.h>
#include <glob.h>
#include "shell.h"
#include "my.h"

static void	skip_to_next(char *str, int *i)
{
  while (str[*i] && is_space(str[*i]))
    *i += 1;
}

static void	glob_stars(t_shell *shell, char *arg, int *i)
{
  char		*file;
  glob_t	list;

  list.gl_offs = 1;
  glob(arg, GLOB_TILDE | GLOB_BRACE, NULL, &list);
  if (list.gl_pathc == 0)
    *i += my_strlen(arg);
  else
    {
      file = construct_alias(list.gl_pathv);
      asprintf(&(shell->line), "%.*s%s%s",
	       *i, shell->line, file,
	       shell->line + *i + my_strlen(arg));
      *i += my_strlen(file);
    }
}

int	parse_stars(t_shell *shell)
{
  char	*str;
  int	i;
  int	start;
  int	len;

  i = 0;
  skip_to_next(shell->line, &i);
  while (i < my_strlen(shell->line))
    {
      len = 0;
      start = i;
      while (shell->line[i + len] && !is_space(shell->line[i + len]))
	len += 1;
      glob_stars(shell, my_strndup(shell->line + start, len), &i);
      skip_to_next(shell->line, &i);
    }
}
