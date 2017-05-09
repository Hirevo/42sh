/*
** term_emul.c for term_emul in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon May  8 18:23:09 2017 Arthur Knoepflin
** Last update Tue May  9 09:47:24 2017 Arthur Knoepflin
*/

#include "shell.h"
#include "my.h"

void	del_last_char(char **prompt)
{
  *prompt = my_strndup(*prompt, my_strlen(*prompt) - 1);
}

void	add_char_dc(char **prompt, char c)
{
  insert_char(prompt, c);
}
