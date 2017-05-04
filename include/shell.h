/*
** shell.h for progammation shell in /home/nicolaspolomack/shell/PSU_2016_minishell1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Jan  3 19:13:06 2017 Nicolas Polomack
** Last update Thu May  4 22:14:31 2017 Arthur Knoepflin
*/

#ifndef SHELL_H_
# define SHELL_H_

# include <sys/stat.h>
# include "server.h"

typedef struct		s_command
{
  char			**av;
  char			link;
  char			*r_name;
  char			*r_type;
  char			*l_name;
  char			*l_type;
  int			count;
  struct s_command	*prev;
  struct s_command	*next;
}			t_command;

typedef struct		s_alias
{
  char			*alias;
  char			*command;
  struct s_alias	*next;
}			t_alias;

/*
** This is the main structure that binds the shell together
**
** env: the environement
** path: the current path
** home: the current home, for prompt & cd builtin
** current: the current working directory, for prompt
** line: raw command input from user
** final: parsed command from line
** hist: last parsed command executed
** hist_args: arg count from hist
** exit: last exit status, for exit builtin
** exit_str: last exit status converted to str, for prompt
** last: used for alias processing, avoids loops
** prev: last working directory, for cd builtin
**
*/
typedef struct		s_shell
{
  char			**env;
  char			**path;
  char			*home;
  char			*current;
  char			*line;
  char			**final;
  char			**hist;
  char			is_done;
  unsigned int		hist_args;
  unsigned int		exit;
  char			*exit_str;
  char			*last;
  char			*prev;
  int			*fds;
  t_alias		*alias;
  t_command		*commands;
  t_command		*cur;
}			t_shell;

unsigned int	count_args(char *);
int	get_next_arg(char *, char **, int);
char	**bufferize(char *, int);
char	*cat_path(char **, char *, int);
void	exec_child(t_shell *, int);
unsigned int	exec_command(char **, t_shell *);
unsigned int	exec_line(t_shell *, unsigned int);
void	parse_path(t_shell *);
int	count_entries(char *);
int	get_next_entry(char *, char **, int);
char	**init_path(char **);
char	**set_default_path();
int	disp_env(char **);
int	move_dir(char **, int, t_shell *);
unsigned int	exec_action(t_shell *, unsigned int);
unsigned int	process_command(t_shell *, int);
char	**add_to_env(char **, char *, char *);
int	is_char_alpha(char *);
void	mod_env(char ***, char *, char *, int);
int	set_env(char ***, char *, char *);
int	unset_env(char ***, char **);
int	remove_env_entry(char ***, int);
char	**copy_env(char **);
char	*get_home(char **);
void	free_shell(t_shell *);
void	free_shell2(t_shell *);
void	free_commands(t_shell *);
int	my_print_err(char *);
int	my_print_ret(char *, int);
int	is_path(char *);
int	is_valid_path(char *);
void	diagnose_status(unsigned int);
int	check_wave(t_shell *);
void	add_hist(t_shell *);
void	my_print_command(t_shell *);
char	*detect_home(char *, char *);
char	*get_current(char *, char *);
int	exec_builtins(t_shell *, int, int *);
int	exec_builtins2(t_shell *, int, int *, int);
unsigned int	get_unsigned_int(char *);
int	is_line_empty(t_shell *);
int	init_shell(t_shell *, char **);
int	my_strlen_spe(char *, char);
void	init_aliases(t_shell *);
void	set_alias(t_shell *, char *);
void	reload_shell(t_shell *);
void	free_alias(t_shell *);
int	disp_alias(t_shell *, char *);
int	disp_all_alias(t_shell *);
int	add_alias(t_shell *, char *, char *);
void	save_alias(t_shell *);
void	write_alias(t_alias *, int);
void	my_print_fd(char *, int);
int	set_commands(t_shell *);
int	check_access(char **, t_shell *);
int	check_env_error(char *);
int	check_exit(t_shell *, int);
int	compare_stats(struct stat *);
void	check_exec(t_shell *, int, int *);
void	exec_piped_command(char *, t_command *, int[2], t_shell *);

/*
** alias3.c
*/
int	parse_alias(t_shell *);

/*
** config.c
*/

int	config_http(t_config *);

/*
** history2.c
*/
int	parse_history(t_shell *);

/*
** exec/exec2.c
*/
unsigned int	exec_redirected_builtins(t_shell *, int, int *, int[2]);

/*
** exec/close.c
*/
int	close_pipes(int *);

/*
** launch_config.c
*/

int	launch_config(t_shell *);

/*
** redirects.c
*/
int	setup_right_redirect(t_command *, int *, int);
int	setup_left_redirect(char *, int);
int	check_redirects(t_command *, t_command *);
int	prepare_redirect(t_command *, char **, char **, int);
int	set_redirects(t_shell *);

/*
** buffer.c
*/
int	buffer_input(char *, int[2]);

/*
** parse/line.c
*/
char	*my_epurstr(char *);
char	*my_epurcommand(char *);

/*
** parse/error.c
*/
int	check_error(t_shell *);

/*
** exec/pipe.c
*/
int	exec_pipeline(t_shell *);
int	father_action(t_command **, int **, int *, t_shell *);
void	exec_piped_child(int *, t_command *, int[2], t_shell *);

/*
** exec/setup.c
*/
void	init_redirect(t_command *, int *, int *, int *);
void	setup_exec(t_command *, int *, int *);

/*
** is.c
*/
int	is_redirect(char *);
int	is_right_redirect(char *);
int	is_left_redirect(char *);
int	is_dir(char *);
int	is_builtin(char *);

/*
** is2.c
*/
int	is_separator(char);
int	is_space(char);
int	is_delimiter(char);

/*
** char.c
*/
void	insert_char(char **, char);
void	insert_int(int **, int);

/*
** print.c
*/
int	ret_error(t_shell *, char *);

/*
** exit.c
*/
int	set_error(t_shell *, int);

#endif /* !SHELL_H_ */
