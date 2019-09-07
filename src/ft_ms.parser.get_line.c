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

#include <minishell.stuctures.h>
#include "libft.h"

char *ms__get_line()
{
	static char buff[3] = { 0 };

	ft_bzero(buff, 2);
	while (!ft_streq(buff, "\n"))
	{
		ft_bzero(buff, 2);
		read(g_ms.fd, buff, 2);
		if (g_ms.ctrl_c)
		{
//			get_line_handle_signal(buff);
			continue;
		}
//		handle_input(buff);
	}
//	ft_strchrreplace(g_ms.line, "\n", 0);
	return (g_ms.buffer->data);
}