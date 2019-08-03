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

#include "minishell.h"

void ms_set_raw()
{
	struct termios termios;

	if (!g_ms.is_raw)
	{
		tcgetattr(STDIN_FILENO, &termios);
		tcgetattr(STDIN_FILENO, &g_ms.termios);
		termios.c_lflag &= ~(ICANON | ECHO);
		termios.c_cc[VMIN] = 1;
		termios.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	}
}