/*
** is_alpha.c for is_alpha in /home/benjamin/Dropbox/func/is_it/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 18:48:46 2017 Benjamin
** Last update Sun Apr  2 21:00:53 2017 Benjamin
*/

#include "bs.h"

int	is_alpha(char c)
{
  return (is_lower(c) || is_upper(c));
}
