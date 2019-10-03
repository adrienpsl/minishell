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

	if (-1 == tcgetattr(STDIN_FILENO, &termios))
		return (-1);
	if (-1 == tcgetattr(STDIN_FILENO, saved_termios))
		return (-1);
	termios.c_lflag &= ~(ICANON | ECHO);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios))
		return (-1);
	return (OK);
}

int main(int ac, char **av, char **env_system)
{
	struct termios termios;
	char **env;

	g_ms_test = 0;
	if (OK != activate_raw_mode(&termios))
		return (EXIT_FAILURE);
	if (NULL == (g_line = fts__init(20)))
		return (EXIT_FAILURE);
	if (NULL == (env = ft_strsplit_copy(env_system, 0)))
		return (EXIT_FAILURE);
	signal(SIGINT, ms_signal_minishell);
	ms__init(&env);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	ft_strsplit_free(&env);
	fts__free(&g_line);
	return (EXIT_SUCCESS);
	ac = (int)av;
}
