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
#include <minishell.defines.h>
#include <minishell.prototypes.h>
#include "libft.h"

static void search_binary()
{
	char *binary_name;

	if (
		NULL != (binary_name =
					 ms__find_binary(
						 g_ms.env,
						 g_ms.current_line->data,
						 g_ms.buffer,
						 MS__FIND_BINARY_COMPLETION
					 )
		))
	{
		ft_putstr_fd(binary_name + g_ms.current_line->length, 1);
		fts__add(g_ms.current_line, binary_name + g_ms.current_line->length);
	}
}

static void print_and_add(char buff[3])
{
	if (
		buff[1] != 0
		)
		return;
	ft_putstr_fd(buff, 1);
	if (
		OK != ft_str_cmp("\n", buff)
		)
		fts__add(g_ms.current_line, buff);
}

static void delete_char()
{
	if (
		g_ms.current_line->length
		)
	{
		fts__remove_from(
			g_ms.current_line,
			g_ms.current_line->length - 1
		);
		ft_putstr_fd("\b \b", 1);
	}
}

static void handle_input(char buff[3])
{
	if (
		OK == ft_str_cmp(MS__DEL, buff)
		)
		delete_char();
	else if (
		OK == ft_str_cmp(MS__TAB, buff)
		)
		search_binary();
	else
		print_and_add(buff);
}

char *ms__get_line(int size_read)
{
	char buff[4] = { 0 };

	while (OK != ft_str_cmp(buff, "\n"))
	{
		*(int *)&buff = 0;
		if (
			read(g_ms.fd, buff, size_read) <= 0
			)
			break;
		if (g_ms.ctrl_c)
		{
			//			get_line_handle_signal(buff);
			continue;
		}
		handle_input(buff);
	}
	return (g_ms.current_line->data);
}