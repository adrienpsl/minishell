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

static char **built_split_argv(char *line)
{
	char **argv;
	char **tmp;

	transform_space(line);
	if (!(argv = ft_strsplit(line, "\2")))
		return (ft_put_ptr(NULL, MS_NO_MEMORY));
	tmp = argv;
	while (*tmp)
	{
		ft_strchrreplace(*tmp, "\2", ' ');
		tmp++;
	}
	return (argv);
}

char *new_line(char *line, int position, char *buffer)
{




	if (line[position] == '~')
	{
		ms_env_get_value("HOME", buffer);
//		length = 1;
	}
	else
	{

	}

	return (line);
}

char *replace_$(char *line, int position, char *buffer)
{
	int length;

	length = ft_strchr(line + position, ' ');
	if (length == -1)
		length = ft_strlen(line + position);
	if (length > MS_MAX_LENGTH_VAR)
		return (NULL);
	line[length] = 0;
	ms_env_get_value(line + 1, buffer);
	line[position] = 0;
	return (ft_strjoinby(line, buffer, line + length, FREE_FIRST));
}

//char *static

int replace_jocker(char **argv)
{
	int position;

	char buffer[MS_SIZE_BUFFER_FULL];
	while (*argv)
	{
		while ((position = ft_strchrstr(*argv, "$~")) > -1)
		{
			if (position > MS_SIZE_BUFFER)
			{
				return (ft_put_int(-1, MS_BUFFER_ERROR));
			}
			ft_bzero(buffer, MS_SIZE_BUFFER_FULL);
			if (*argv[position] == '$')
			{
			}
			if (*argv[position] == '~')
			{

			}
		}

		argv++;
	}
	return (0);
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
	if (!(argv = built_split_argv(line)))
	{
		return (-1);
	}

	*out = argv;

	//	if (!(line = ms_parser_replace_special(line, '$')))
	//	{
	//		return (ft_put_int(-1, MS_NO_MEMORY));
	//	}
	//	if (!(argv = ms_parser_build_argv(line)))
	//	{
	//		return (-1);
	//	}
	//	*out = argv;
	free(line);
	return (0);
}
