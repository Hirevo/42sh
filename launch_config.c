/*
** launch_config.c for launch_config in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May  4 20:40:56 2017 Arthur Knoepflin
** Last update Fri May  5 02:14:30 2017 Nicolas Polomack
*/

#include "shell.h"
#include "server.h"
#include "get_next_line.h"

int		launch_config(t_shell *shell)
{
  int		ret;
  t_config	config;

  config.env = environ;
  config.prompt = shell->prompt;
  ret = config_http(&config);
  shell->prompt = config.prompt;
  return (ret);
}
