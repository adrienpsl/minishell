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

static int ms_is_quote_match(char *command)
{
	char current_quote;

	if (!command)
		return (1);
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

char *ms_test_input_line()
{
	int		ret;
	char	*current_line;
	char	*tmp;

	if (get_next_line(g_ms.fd, &current_line, 0) < 1)
		return (NULL);
	while (!ms_is_quote_match(current_line))
	{
		ft_printf("quotes>  ");
		tmp = current_line;
		if ((ret = get_next_line(g_ms.fd, &current_line, 0)) == -1)
			return (NULL);
		if (ret
			&& !(current_line = ft_strjoinby(tmp, "\n", current_line,
											 FREE_FIRST | FREE_THIRD)))
			return (NULL);
	}
	return (current_line);
}

char *handle_input(char buff[3], char *line)
{
	char *find;

	if (ft_streq(MS_DEL, buff))
	{
		line[ft_strlen(line) - 1] = 0;
		ft_putstr_fd("\b \b", 1);
	}
	else if (ft_streq(MS_TAB, buff))
	{
		find = ms_find_binary(line, 1);
		if (find)
		{
			ft_putstr_fd(find + ft_strlen(line), 1);
			free(line);
			return (find);
		}
	}
	else if (!buff[1])
	{
		ft_putstr_fd(buff, 2);
		return (ft_strjoin(line, buff, FREE_FIRST));
	}
	return (line);
}

char *get_line()
{
	char *line;
	static char buff[3] = { 0 };

	if (!(line = ft_strnew(0)))
		return (NULL);
	while (!ft_streq(buff, "\n"))
	{
		if (g_ms.ctrlc)
		{
			ft_str_free(&line);
			line = ft_strdup(buff);
			g_ms.ctrlc = 0;
		}
		ft_bzero(buff, 2);
		read(g_ms.fd, buff, 2);
		if (!(line = handle_input(buff, line)))
			return (NULL);
	}
	line[ft_strlen(line) - 1] = 0;
	return (line);
}

char *ms_get_new_line()
{
	char *current_line;
	char *tmp;

	current_line = get_line();
	while (!ms_is_quote_match(current_line))
	{
		ft_printf("quotes>  ");
		tmp = current_line;
		if (!(current_line = get_line()))
		{
			ft_str_free(&tmp);
			return (NULL);
		}
		if (!(current_line = ft_strjoinby(tmp, "\n", current_line,
										  FREE_FIRST | FREE_THIRD)))
			return (NULL);
	}
	return (current_line);
}