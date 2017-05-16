/*
** match.c for match in /home/arthur/delivery/CPool_match-nmatch/
**
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
**
** Started on  Sat Oct 15 18:43:19 2016 Arthur Knoepflin
** Last update	Tue May 16 19:04:03 2017 Full Name
*/

#include <stdlib.h>
#include "my.h"
#include "auto_complete.h"
#include "shell.h"

void		transform(t_shell *shell, t_auto *t, t_match **list, char **s)
{
  shell->is_comp = 0;
  *s ? free(shell->line) : 0;
  shell->line = my_strcatdup(t->pre_token, (*list)->cmd);
  shell->line = my_fstrcat(shell->line, t->post_token, 1);
  if (t->is_a_dir)
    {
      t->is_a_dir = 0;
      shell->line = my_fstrcat(shell->line, "/", 1);
    }
  (*list)->cmd = delete_str(*s, (*list)->cmd);
  if (t->post_token)
    *s = my_strcatdup((*list)->cmd, t->post_token);
  shell->line = my_fstrcat(shell->line, " ", 1);
  shell->w.cur = my_strlen(shell->line);
}

int	match(char *s1, char *s2)
{
  int	ret;

  if (*s1 == '\0' && *s2 == '\0')
    return (1);
  else if (*s2 == '*' && *s1 == '\0')
    ret = match(s1, s2 + 1);
  else if (*s2 == '*')
    ret = (match(s1, s2 + 1) || match(s1 + 1, s2));
  else if (*s1 == *s2)
    ret = match(s1 + 1, s2 + 1);
  else
    return (0);
  return (ret);
}
