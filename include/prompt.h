/*
** prompt.h for prompt in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May  4 23:40:30 2017 Arthur Knoepflin
** Last update Fri May  5 00:49:48 2017 Arthur Knoepflin
*/

#ifndef PROMPT_H_
# define PROMPT_H_

# include "shell.h"

void	turbosh_prompt(t_shell *);
void	bash_prompt(t_shell *);
void	tcsh_prompt(t_shell *);
void	minimalist_prompt(t_shell *);

#endif /* !PROMPT_H_ */
