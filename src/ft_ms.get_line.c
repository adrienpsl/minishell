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

/*
**	delete in the screen and buffer the last char written by the user
*/

void			delete_last_char(t_s *const line)
{
	ft_putstr_fd("\b \b", 1);
	if (line->length)
		fts__remove_from(line, line->length - 1);
}

/*
**	delete all the char written by the user
*/

void			clean_char(t_s *const line)
{
	while (line->length)
		delete_last_char(line);
}

/*
**	try to find in path if it exist a command that start by the current line
**	if it, will print and add it to the screen / buffer
*/

void			tab_char(
	char **env,
	t_s *const line)
{
	static char		*found = NULL;
	static char		**split = NULL;
	int				count;

	if (NULL != (found = (char *)ms__search_binary((char **)env, line->data,
		ftstr__search_start))
		&& NULL != (split = ft_strsplit(found, "/")))
	{
		if (0 < (count = ft_strsplit_count(split)))
		{
			clean_char(line);
			OK == fts__add(line, split[count - 1])
			&& ft_printf(line->data);
		}
	}
	ftstr__free((char **)&found);
	ft_strsplit_free(&split);
}

/*
**	dispatch according to the current chan to the del / tab / add function
*/

static void		handle_input(
	char **env,
	const char *buffer,
	t_s *const line)
{
	if (OK == ft_strcmp(MS__DEL, buffer))
		delete_last_char(line);
	else if (OK == ft_strcmp(MS__TAB, buffer))
		tab_char(env, line);
	else if ('\0' == buffer[1])
	{
		ft_printf(buffer);
		fts__add(line, (char *)buffer);
	}
}

/*
**	buffering the user content until he write \n,
**	put in output the buffer start
*/

int				ms__get_line(
	char **env,
	t_s *const line,
	char **output)
{
	static char buffer[5] = { 0 };

	fts__clear(line);
	ft_bzero(&buffer, 5);
	while (OK != ft_strcmp(buffer, "\n"))
	{
		ft_bzero(&buffer, 5);
		if (read(0, buffer, 4) < 0)
			return (-1);
		if (OK != ft_strcmp(buffer, "\n"))
			handle_input(env, buffer, line);
	}
	ft_printf("\n");
	*output = line->data;
	return (OK);
}
