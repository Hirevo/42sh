/*
** auto_complete.c for auto in /home/Maxime/delivery/PSU/PSU_2016_42sh/auto_completation/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Tue May  9 20:38:46 2017 Maxime Jenny
** Last update	Tue May 16 18:45:21 2017 Full Name
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include "auto_complete.h"
#include "shell.h"
#include "my.h"
#include "prompt.h"

static int	find_matches(t_match **list, char *path, char *str, t_auto *t)
{
  struct dirent	**namelist;
  int		n;
  int		size;
  char		*str2;

  if ((size = scandir(path, &namelist, NULL, NULL)) <= 0)
    return (0);
  if (size == 1 && strcmp(namelist[0]->d_name, str) == 0)
    return (-1);
  n = size - 1;
  str2 = my_strcatdup(str, "*");
  while (n >= 0)
    {
      if (match(namelist[n]->d_name, str2) == 1)
	{
	  if ((add_in_autolist(list, strdup(namelist[n]->d_name))) == -1)
	    return (-1);
	  t->is_a_dir = (namelist[n]->d_type == DT_DIR) ? (1) : (0);
	}
      n--;
    }
  free(str2);
  my_free_dirent(namelist, size);
  return (0);
}

int		modify_path(t_auto *token, char **path)
{
  int		i;
  char		*str;

  i = 0;
  if ((find_a_path(path, token)) == -1)
    return (-1);
  if (token->is_path == 1)
    return (0);
  if (token->pre_token[0] == 0)
    return (0);
  str = token->pre_token;
  while (str[i])
    i++;
  while (i >= 0 && str[i] == ' ')
    i--;
  if (str[i] == ';')
    return (0);
  *path = ".";
  return (0);
}

static char		*delete_str(char *to_del, char *content)
{
  int			i;
  int			m;
  char			*str;

  if (my_strlen(to_del) > my_strlen(content))
    return (to_del);
  i = 0;
  while (to_del && to_del[i] && content[i] && to_del[i] == content[i])
    i++;
  if ((str = malloc(my_strlen(content) - i + 2)) == NULL)
    return (NULL);
  m = 0;
  while (content && content[i])
    str[m++] = content[i++];
  str[m] = 0;
  return (str);
}

static void		transform(t_shell *shell, t_auto *t, t_match **list,
				  char **s)
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
  shell->w.cur = strlen(shell->line);
}

static void		reprint_and_free(t_shell *shell, t_match **list,
					 t_auto *t, int is_dir)
{
  char			*s;

  s = t->token ? strdup(t->token) : NULL;
  if (*list)
    {
      if ((*list)->next == NULL)
	transform(shell, t, list, &s);
      shell->is_comp > 0 ? show_autolist(shell, *list, is_dir) : 0;
      shell->is_comp > 0 ? print_prompt(shell) : 0;
      shell->is_comp > 0 ? my_putstr(shell->line ? shell->line : "") : 0;
      my_strcmp(s, t->token) ? my_putstr(s) : 0;
    }
  shell->is_comp++;
  destroy_the_list(list);
  free(s);
  free(t->token);
}

int		auto_complete(t_shell *shell, char *path)
{
  char		**parsed;
  int		i;
  int		err;
  t_auto	token;
  t_match	*list;

  if ((find_token(shell, &token)) == -1)
    return (-1);
  token.is_path = 0;
  modify_path(&token, &path);
  if (!path || !(parsed = split_it(path, ":")))
    return (-1);
  list = NULL;
  i = 0;
  err = 0;
  while (parsed[i] && err != 1)
    {
      if ((err = find_matches(&list, parsed[i++], token.token, &token)) == -1)
	return (-1);
    }
  my_free_tab((void **)parsed);
  reprint_and_free(shell, &list, &token, strcmp(path, ".") == 0);
  free(token.pre_token);
  free(token.post_token);
  return (0);
}
