/*
** nb_args.c for nb_args in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 23:03:13 2017 Arthur Knoepflin
** Last update Thu Apr  6 18:23:31 2017 Arthur Knoepflin
*/

int	nb_args(char **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i])
    i += 1;
  return (i);
}
