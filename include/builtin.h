/*
** builtin.h for builtin in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon May 15 13:38:58 2017 Arthur Knoepflin
** Last update Thu May 18 21:10:14 2017 Nicolas Polomack
** Last update Thu May 18 23:08:14 2017 Arthur Knoepflin
*/

#ifndef BUILTIN_H_
# define BUILTIN_H_

typedef struct	s_parse_env
{
  int		ignore;
  int		null;
  int		unset;
  char		**unset_l;
  char		**cmd;
}		t_parse_env;

int		alias(t_shell *, int);
int		cd_b(t_shell *, int);
int		config_b(t_shell *, int);
int		dualcast_b(t_shell *, int);
int		echo_b(t_shell *, int);
int		exit_b(t_shell *, int);
int		setenv_b(t_shell *, int);
int		unalias_b(t_shell *, int);
int		unsetenv_b(t_shell *, int);
int		prompt(t_shell *, int);
int		env_b(t_shell *, int);
t_parse_env	*parse_env(char **);

/*
** check_file.c
*/

int	print_error_path(char *);
int	print_error(char *);

/*
** check_file_2.c
*/

int	is_folder(char *);

/*
** exec_arg.c
*/

int	is_in_env(char *, char);
void	free_char_double(char **);
int	exec_arg(char *, char **, char **);

/*
** exec_arg_2.c
*/

void	exec_not_path(char *, char **, char **);

/*
** env.c
*/

void	show_tab_env(char **);

/*
** env_checkerror.c
*/

int	cherror_env_parse(char **);

/*
** env_cherror.c
*/

int	is_alpha_err(char *, int);

/*
** launch_soft.c
*/

int	launch_soft(t_parse_env *);

/*
** shw_env_parse;
*/

int	str_in_liste(char **, char *);
void	show_env_parse(t_parse_env *);

/*
** show_signal.c
*/

int	show_signal(int);

#endif /* !BUILTIN_H_ */
