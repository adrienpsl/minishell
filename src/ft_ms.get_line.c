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
#include <ft_mem.h>

void delete_char(t_s *const line)
{
	ft_putstr_fd("\b \b", 1);
	if (line->length)
		fts__remove_from(line, line->length - 1);
}

void clean_char(t_s *const line)
{
	while (line->length)
		delete_char(line);
}

void tab_char(
	const char *const *const env,
	t_s *const line)
{
	const char *found;

	if (NULL != (found = ms__search_binary((char **)env, line->data)))
	{
		clean_char(line);
		if (OK == fts__add(line, (char *)found))
			ft_printf(line->data);
		ftstr__free((char **)&found);
	}
}

void handle_input(
	const char *const *const env,
	char const buffer[4],
	t_s *const line)
{
	if (OK == ft_strcmp(MS__DEL, buffer))
		delete_char(line);
	else if (OK == ft_strcmp(MS__TAB, buffer))
		tab_char(env, line);
	else if ('\0' == buffer[1])
	{
		ft_printf(buffer);
		fts__add(line, (char *)buffer);
	}
}

// get the current line with the buffer t_s
// and put his content to the output
int *ms__get_line(
	const char *const *const env,
	t_s *const line,
	char **output)
{
	char buffer[5] = { 0 };

	fts__clear(line);
	while (OK != ft_strcmp(buffer, "\n"))
	{
		ft_bzero(&buffer, 5);
		if (read(0, buffer, 4) <= 0)
			break;
		if (OK != ft_strcmp(buffer, "\n"))
			handle_input(env, buffer, line);
	}
	*output = line->data;
	return (OK);
}
