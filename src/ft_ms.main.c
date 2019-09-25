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
#include <minishell.h>
#include <ft_mem.h>

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

int ms__loop(char **commands, t_env *e)
{
	while (NULL != *commands)
	{
		if (MS__EXIT == ms__command(*commands, e))
			return MS__EXIT;
		commands += 1;
	}
	return (OK);
}

int clean_and_quit(t_env *e, char **command, char *line, int ret,
				   struct termios *termios)
{
	free_env(e);
	ft_strsplit_free(&command);
	ftstr__free(&line);
	tcsetattr(STDIN_FILENO, TCSANOW, termios);
(void)termios;
	return (ret);
}

char **get_command_split(const char **env)
{
	char *line;

	ms__get_line(env, g_line, &line);

	return (NULL);
}

int ms__init(char **env_system)
{
	t_env e;
	char *line;
	char **command;
	struct termios termios;

	ms__activate_raw_mode(&termios);
	g_line = fts__init(20);
	e.tmp_env = NULL;
	if (NULL == (e.env = ft_strsplit_copy(env_system, 0)))
		return (EXIT_FAILURE);
	line = NULL;
	print_promp();
	while (OK == ms__get_line((void *)e.env, g_line, &line)
		   && OK == replace_dollar_tilde((void *)e.env, (void *)&line))
	{
		if (NULL == (command = ft_strsplit(line, ";")))
			return (clean_and_quit(&e, command, line, EXIT_FAILURE, &termios));
		if (MS__EXIT == ms__loop(command, &e))
			return (clean_and_quit(&e, command, line, EXIT_SUCCESS, &termios));
		free(line);
		print_promp();
	}
	return (clean_and_quit(&e, command, line, EXIT_FAILURE, &termios));
}
