/*
** shell.h for 42sh in /home/nicolaspolomack/curses
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Apr 18 14:21:08 2017 Nicolas Polomack
** Last update Tue Apr 18 19:14:59 2017 Nicolas Polomack
*/

#ifndef SHELL_H_
# define SHELL_H_

# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define RESET "\033[0m"

# include <termio.h>

typedef struct	s_window
{
  struct termio	oterm;
  char		*clear;
  char		*forw;
  char		*backw;
  int		cur;
}		t_window;

typedef struct	s_shell
{
  t_window	w;
  char		*line;
  char		*cwd;
  int		tty;
}		t_shell;

/*
** init.c
*/
void	init(t_shell *);
void	init_prompt(t_shell *);

/*
** misc.c
*/
char	get_input();
void	handle_error(char *);

/*
** char.c
*/
void	insert_char(char **, char, int);
void	delete_char(char **, int);

/*
** actions.c
*/
void	remove_char(t_shell *);
void	add_char(t_shell *, char);
void	move_cursor(t_shell *, char);
void	clear_term(t_shell *);
void	pos_cursor(t_shell *);

/*
** prompt.c
*/
void	prompt_line(t_shell *);

#endif /* !SHELL_H_ */
