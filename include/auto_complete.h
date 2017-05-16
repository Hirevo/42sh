/*
** auto_complete.h for auto in /home/Maxime/perso/autocompleter/include/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Tue May  9 13:51:20 2017 Maxime Jenny
** Last update	Tue May 16 15:36:26 2017 Full Name
*/

#ifndef AUTO_COMPLETE_H_
# define AUTO_COMPLETE_H_

# include <dirent.h>
# include "shell.h"

typedef struct		s_auto
{
  char			*pre_token;
  char			*token;
  char			*post_token;
  int			is_path;
}			t_auto;

typedef struct		s_match
{
  char			*cmd;
  struct s_match	*next;
}			t_match;

int		auto_complete(t_shell *shell, char *path);
int		match(char *s1, char *s2);
char		**split_it(char *str, char *to_split);
int		word_length(char *str, int i, char *to_split);
void		my_free_dirent(struct dirent **tab, int size);
void		my_free_tab(void **tab);
int		find_a_path(char **path, t_auto *token);

/*
** List
*/

int		add_in_autolist(t_match **list, char *cmd);
void		show_autolist(t_shell *, t_match *, int);
void		destroy_the_list(t_match **list);

/*
** Tokens
*/

int		find_token(t_shell *shell, t_auto *token);

#endif /* !AUTO_COMPLETE_H_ */
