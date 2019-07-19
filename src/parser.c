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
			ft_strchrnreplace(line, " \t", '|', end);
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
	char *value;

	if (!(key = ft_strndup(line, end)))
		return (NULL);
	value = ms_env_get_value(key, g_ms.env);
	free(key);
	return (value ? value : "");
}

// here I do a buffer for that line, I limit the max size
// case it's so pain full sinon.
// I limit the size, but if I want replace by the $env,
// how I can do that?
// I double the size of the max line by that,
// and each time I add variable, I count and return
// error if too long. seem very power full
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

	if (!(argv = ft_str_split(line, " \t")))
		return (NULL);
	tmp = argv;
	while (*tmp)
	{
		ft_strchrreplace(*tmp, "|", ' ');
		tmp++;
	}
	return (argv);
}

char **ms_parser_read_command()
{
	char *line;
	char **argv;

	if (!(line = ms_parser_get_commands()))
		return (NULL);
	ms_parser_transform_space(line);
	line = ms_parser_replace_$(line);
	if (!(argv = ms_parser_build_argv(line)))
		return (NULL);
	free(line);
	return (argv);
}
