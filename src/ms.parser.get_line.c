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

// here I need to call the completion stuff 

char *handle_input(char buff[3], char *line)
{
	char *find;

	if (ft_streq(MS_DEL, buff))
	{
		line[ft_strlen(line) - 1] = 0;
		ft_putstr_fd("\b \b", 1);
		return (line);
	}
	else if (ft_streq(MS_TAB, buff))
	{
		printf("\n %s \n", line);
		find = ms_find_binary(line, 1);
		if (find)
			printf("%s \n", find);
		return (line);
	}
	else if (!buff[1])
	{
		ft_putstr_fd(buff, 2);
		return (ft_strjoin(line, buff, FREE_FIRST));
	}
	return line;
}

char *get_line()
{
	char *line;
	char buff[3];

	ft_bzero(buff, 3);
	line = ft_strnew(0);
	while (!ft_streq(buff, "\n"))
	{
		ft_bzero(buff, 2);
		read(g_fd, buff, 2);
		if (!(line = handle_input(buff, line)))
			return (NULL);
	}
	return (line);
}

static int ms_is_quote_match(char *command)
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

char *ms_parser_get_commands()
{
	char *current_line;
	char *tmp;

	ms_activate_canonical(1);
	current_line = get_line();
	while (!ms_is_quote_match(current_line))
	{
		ft_printf("quotes>  ");
		tmp = current_line;
		if (!(current_line = get_line()))
			return (NULL);
		if (!(current_line = ft_strjoinby(tmp, "\n", current_line,
										  FREE_FIRST | FREE_THIRD)))
			return (NULL);
	}
	return (current_line);
}