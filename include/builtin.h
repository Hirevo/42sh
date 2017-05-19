/*
** builtin.h for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri May 19 19:22:19 2017 Nicolas Polomack
** Last update Fri May 19 19:22:20 2017 Nicolas Polomack
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
