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

int is_quote_paired(char *command)
{
	char current_quote;

	current_quote = 0;
	while (*command)
	{
		if (current_quote && *command == current_quote)
			current_quote = 0;
		else if (!current_quote && ft_strchr("'\"", *command) > -1)
			current_quote = *command;
		command++;
	}
	return (current_quote ? 0 : 1);
}

char *get_all_commands()
{
	char *current_line;
	char *tmp;
	int ret;

	if (get_next_line(g_fd, &current_line, 0) == -1)
		return (NULL);
	while (!is_quote_paired(current_line))
	{
		ft_printf("quotes>  ");
		// TODO : mettre un join by and add in lib free option
		tmp = current_line;
		if ((ret = get_next_line(g_fd, &current_line, 0)) == -1)
			return (NULL);
		if (ret && !(current_line = ft_strjoin(current_line, "\n", FREE_FIRST)))
			return (NULL);
		if (ret && !(current_line = ft_strjoin(current_line, tmp, FREE_FIRST | FREE_SECOND)))
			return (NULL);
	}
	return (current_line);
}

void transform_space(char *line)
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



char **build_argv(char *line)
{
	char **argv;
	char **tmp;

	transform_space(line);
	if (!(argv = ft_str_split(line, " \t")))
	    return (NULL);
	tmp = argv;
	while (*tmp)
	{
	    tmp++;
	}
	return (argv);
}

// parse str,
// mix split.


//int ms_parse_command(char *command, t_ms *ms)
//{
//	char **command_split;

//	if (! ft_str_split(command, &command_split, FT_CHAR_SPACE))
//		return (MEMORY_LACK);
// TODO : handle that error
//	if (command_split == NULL)
//	    return (1);
//	(void)ms;
//	ms->arg = command_split;
//	return (0);
//}
