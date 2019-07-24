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

static void ms_parser_transform_space(char *line)
{
	int start;
	int end;

	while (*line)
	{
		if ((start = ft_strchrstr(line, "\'\"")) > -1)
		{
			line += start;
			end = ft_strchr(line + 1, line[0]) + 1;
			ft_strchrnreplace(line, " \t", '\2', end);
			line[0] = ' ';
			line[end] = ' ';
			line += end;
			continue;
		}
		line++;
	}
}

static char *ms_parser_find_$(char *line, int end)
{
	char *key;
	static char buff[MS_SIZE_BUFFER_FULL];

	ft_bzero(buff, MS_SIZE_BUFFER_FULL);
	if (!(key = ft_strndup(line, end)))
		return (NULL);
	ms_env_get_value(key, buff);
	free(key);
	return (buff);
}

static char *ms_parser_replace_$(char *line)
{
	int start;
	int end;
	char *value;
	char *current;

	while ((start = ft_strchr(line, '$')) > -1)
	{
		current = line + start;
		end = ft_strchr(current, ' ');
		end = end == -1 ? ft_strlen(current) : end;
		if (!(value = ms_parser_find_$(current + 1, end)))
			return (NULL);
		line[start] = 0;
		line = ft_strjoinby(line, value, current + end, FREE_FIRST);
	}
	return (line);
}

static char **ms_parser_build_argv(char *line)
{
	char **argv;
	char **tmp;

	if (!(argv = ft_strsplit(line, " \t")))
		return (NULL);
	tmp = argv;
	while (*tmp)
	{
		ft_strchrreplace(*tmp, "\2", ' ');
		tmp++;
	}
	return (argv);
}

int ms_parser(char ***out)
{
	char buffer[MS_SIZE_BUFFER_FULL];
	char *line;
	char **argv;

	bzero(buffer, MS_SIZE_BUFFER_FULL);
	if (!(line = ms_parser_get_commands()))
	{
		return (-1);
	}
	ms_parser_transform_space(line);
	if (!(line = ms_parser_replace_$(line)))
	{
		return (ft_put_int(-1, MS_NO_MEMORY));
	}
	if (!(argv = ms_parser_build_argv(line)))
	{
		return (-1);
	}
	*out = argv;
	free(line);
	return (0);
}
