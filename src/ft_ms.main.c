/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpusel <adpusel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:48:07 by adpusel           #+#    #+#             */
/*   Updated: 2017/11/16 12:45:50 by adpusel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.prototypes.h>

void ms__activate_raw_mode(struct termios *saved_termios)
{
	struct termios termios;
	// TODO :  check the return system

	tcgetattr(STDIN_FILENO, &termios);
	tcgetattr(STDIN_FILENO, saved_termios);
	termios.c_lflag &= ~(ICANON | ECHO);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

int ms__command(char *line, char ***env);
int ms__loop(char **commands, char ***env)
{
	while (NULL != *commands)
	{
		if (2 == ms__command(*commands, env))
			break;
		commands += 1;
	}
	return (OK);
}

int ms__init(char **env_system)
{
	char **env;
	char *line;
	char **command;

	if (NULL == (env = ft_strsplit_copy(env_system, 0)))
		return (-1);
	while (NULL != (line = ms__get_line(env)))
	{
		if (NULL == (command = ft_strsplit(line, ";")))
			return (-1);
		if (2 == ms__loop(command, &env))
			return (OK);
	}
	return (OK);
}
