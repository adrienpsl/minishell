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

#include <minishell.prototypes.h>
#include <ft_mem.h>
#include <minishell.defines.h>

void delete_char(t_s *line)
{
	ft_putstr_fd("\b \b", 1);
	if (line->length)
		fts__remove_from(line, line->length - 1);
}

void clean_char(t_s *line)
{
	while (line->length)
		delete_char(line);
}

void tab_char(t_s *line, char **env)
{
	char *found;

	if (NULL != (found = ms__search_binary(env, line->data)))
	{
		clean_char(line);
		if (OK == fts__add(line, found))
			ft_printf(line->data);
		free(found);
	}
}

void handle_input(char buffer[4], t_s *line, char **env)
{
	if (OK == ft_strcmp(MS__DEL, buffer))
		delete_char(line);
	else if (OK == ft_strcmp(MS__TAB, buffer))
		tab_char(line, env);
	else if ('\0' == buffer[1])
	{
		ft_printf(buffer);
		fts__add(line, buffer);
	}
}

char *ms__get_line(char **env)
{
	char buffer[5] = { 0 };

	while (OK != ft_strcmp(buffer, "\n"))
	{
		ft_bzero(&buffer, 5);
		if (read(0, buffer, 4) <= 0)
			break;
		if (OK != ft_strcmp(buffer, "\n"))
			handle_input(buffer, g_line, env);
	}
	return (NULL);
}
