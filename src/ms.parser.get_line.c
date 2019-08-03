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

char *ms_test_input_line()
{
	char *current_line;

	if (get_next_line(g_ms.fd, &current_line, 0) < 1)
		return (NULL);
	return (current_line);
}

void handle_input(char buff[3])
{
	char *find;

	if (g_ms.line == NULL)
		return;
	if (ft_streq(MS_DEL, buff))
	{
		g_ms.line[ft_strlen(g_ms.line) - 1] = 0;
		ft_putstr_fd("\b \b", 1);
	}
	else if (ft_streq(MS_TAB, buff))
	{
		find = ms_find_binary(g_ms.line, 1);
		if (find)
		{
			ft_putstr_fd(find + ft_strlen(g_ms.line), 1);
			ft_str_free(&g_ms.line);
			g_ms.line = find;
		}
	}
	else if (!buff[1])
	{
		ft_putstr_fd(buff, 2);
		g_ms.line = ft_strjoin(g_ms.line, buff, FREE_FIRST);
	}
}

char *ms_get_line()
{
	static char buff[3] = { 0 };

	g_ms.line = ft_strnew(0);
	if (g_ms.ctrlc)
	{
		if (buff[0] == '\n')
		{
			ft_printf("\n");
			ms_print_prompt();
		}
		g_ms.ctrlc = 0;
	}
	ft_bzero(buff, 2);
	while (!ft_streq(buff, "\n"))
	{
		ft_bzero(buff, 2);
		read(g_ms.fd, buff, 2);
		if (g_ms.ctrlc)
		{
			ft_str_free(&g_ms.line);
			return (NULL);
		}
		handle_input(buff);
	}
	ft_strchrreplace(g_ms.line, "\n", 0);
	return (g_ms.line);
}
