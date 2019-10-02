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

int activate_raw_mode(struct termios *saved_termios)
{
	struct termios termios;

	tcgetattr(STDIN_FILENO, &termios);
	tcgetattr(STDIN_FILENO, saved_termios);
	termios.c_lflag &= ~(ICANON | ECHO);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	return (OK);
}


int main(int ac, char **av, char **env_system)
{
	struct termios termios;
	char **env;

	g_test = 0;
	if (NULL == (env = ft_strsplit_copy(env_system, 0)))
		return (EXIT_FAILURE);
	activate_raw_mode(&termios);
	signal(SIGINT, ms_signal_minishell);
	g_line = fts__init(20);
	ms__init(&env);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	ft_strsplit_free(&env);
	fts__free(&g_line);
	return (EXIT_SUCCESS);
	ac = (int)av;
}
