/*
** builtin.h for builtin in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon May 15 13:38:58 2017 Arthur Knoepflin
** Last update Tue May 16 02:16:59 2017 Arthur Knoepflin
*/

#ifndef BUILTIN_H_
# define BUILTIN_H_

int	alias(t_shell *, int);
int	cd_b(t_shell *, int);
int	config_b(t_shell *, int);
int	dualcast_b(t_shell *, int);
int	echo_b(t_shell *, int);
int	exit_b(t_shell *, int);
int	setenv_b(t_shell *, int);
int	unalias_b(t_shell *, int);

#endif /* !BUILTIN_H_ */
