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

#include <sys/termios.h>
#include "minishell.h"

void ms_activate_canonical(int activate)
{
	static struct termios real_termios;
	struct termios current_termios;

	if (activate == 1)
	{
		tcgetattr(STDIN_FILENO, &real_termios);
		tcgetattr(STDIN_FILENO, &current_termios);
		current_termios.c_lflag &= ~(ICANON | ECHO);
		current_termios.c_cc[VMIN] = 1;
		current_termios.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &current_termios);
	}
	if (!activate)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &real_termios);
	}
}
