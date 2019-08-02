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

/*
**	replace all the space inside good ' ' by \02
*/
static void transform_space(char *line)
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

static char **generate_argv(char *line)
{
	char **argv;
	char **tmp;

	transform_space(line);
	if (!(argv = ft_strsplit(line, " ")))
		return (ft_put_ptr(NULL, MS_NO_MEMORY));
	tmp = argv;
	while (*tmp)
	{
		ft_strchrreplace(*tmp, "\2", ' ');
		tmp++;
	}
	return (argv);
}

/**
 * @brief
 * @param line
 * @param position
 * @param key_length
 * @return
 */
char *get_value(char *line, int position, int *key_length)
{
	char *key;
	char *value;

	if (line[position] == '~')
	{
		*key_length = 1;
		key = ft_strdup("$HOME");
	}
	else
	{
		*key_length = ft_strchr(line + position, ' ');
		*key_length == -1 ? *key_length = ft_strlen(line + position) : 0;
		key = ft_strndup(line + position, *key_length);
	}
	if (!key)
		return (NULL);
	value = ms_get_value(key + 1);
	free(key);
	return (value ? value : "");
}

char *ms_replace_expansions(char *line)
{
	int position;
	int key_end;
	char *value;

	while ((position = ft_strchrstr(line, "$~")) > -1)
	{
		if (!(value = get_value(line, position, &key_end)))
			return (NULL);
		line[position] = 0;
		if (!(line = ft_strjoinby(line, value, line + position + key_end,
								  FREE_FIRST)))
			return (NULL);
	}
	return (line);
}

int ms_parser(char ***out)
{
	char *line;
	char **argv;
	char **tmp;

	line = g_ms.is_test ?
		   ms_test_input_line() :
		   ms_get_new_line();
	if (!(line) || !(argv = generate_argv(line)))
		return (-1);
	tmp = argv;
	while (*tmp)
	{
		*tmp = ms_replace_expansions(*tmp);
		tmp++;
	}
	*out = argv;
	free(line);
	return (0);
}
