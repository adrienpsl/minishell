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
#include "libft.h"

void signal_program(int t)
{
	(void) t;
	ft_printf("\n");
}

void signal_minishell(int sign)
{
	(void) sign;
	ft_printf("\n$> ");
}


void ms_clear_buffer()
{
	ft_bzero(g_ms.buffer, MS_SIZE_BUFFER);
}


int ms_test_file(char *path, char *builtin)
{

	if (!path || access(path, F_OK))
	{
		ft_printf("%s: no such file or directory: %s\n", builtin, path);
		return (-1);
	}
	if (access(path, R_OK))
	{
		ft_printf("%s: permission denied: %s\n", builtin, path);
		return (-1);
	}
	if (access(path, X_OK))
	{
		ft_printf("%s: execution denied: %s\n", builtin, path);
		return (-1);
	}
	return (0);
}
