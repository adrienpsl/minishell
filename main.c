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

#include <minishell.h>

void ms__activate_raw_mode(struct termios *saved_termios)
{
	struct termios termios;

	tcgetattr(STDIN_FILENO, &termios);
	tcgetattr(STDIN_FILENO, saved_termios);
	termios.c_lflag &= ~(ICANON | ECHO);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

int ms__command(char *line, t_env *e)
{
	char **start;
	t_data d;

	ft_bzero(&d, sizeof(t_data));
	if ('\0' == *line)
		return (OK);
	if (NULL == (d.argv = ft_strsplit(line, " ")))
		return (-1);
	start = d.argv;
	d.ret = ms__dispatch(&d, e);
	ft_strsplit_free(&e->tmp_env);
	ft_strsplit_free(&start);
	return (d.ret == MS__EXIT ? 1 : 0);
}

static int get_command_split(t_env *e, char ***output)
{
	char *line;

	if (OK == ms__get_line((void *)e->env, g_line, &line)
		&& OK == replace_dollar_tilde((void *)e->env, (void *)&line))
	{
		*output = ft_strsplit(line, ";");
		ftstr__free(&line);
		if (*output)
			return (OK);
	}
	return (-1);
}

int ms__init(t_env *e)
{
	char **command;

	print_promp();
	while (OK == get_command_split(e, &command))
	{
		if (-1 != ft_strsplit_search(command, (void *)ms__command, e))
			break;
		print_promp();
		ft_strsplit_free(&command);
	}
	ft_strsplit_free(&command);
	return (OK);
}

int main(int ac, char **av, char **env_system)
{
	struct termios termios;
	t_env e = { 0, 0 };

	if (NULL == (e.env = ft_strsplit_copy(env_system, 0)))
		return (EXIT_FAILURE);
	ms__activate_raw_mode(&termios);
	signal(SIGINT, ms_signal_minishell);
	g_line = fts__init(20);
	ms__init(&e);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	free_env(&e);
	fts__free(&g_line);
	return (1);
	ac = (int)av;
}
