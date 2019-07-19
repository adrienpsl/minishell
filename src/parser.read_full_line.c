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
	int ret;

	if ( get_next_line(g_mst.fd, &current_line, 0) < 1)
		return (NULL);
	while (!ms_is_quote_match(current_line))
	{
		ft_printf("quotes>  ");
		tmp = current_line;
		if ((ret = get_next_line(g_mst.fd, &current_line, 0)) == -1)
			return (NULL);
		if (ret && !(current_line = ft_strjoinby(tmp, "\n", current_line,
												 FREE_FIRST | FREE_THIRD)))
			return (NULL);
	}
	return (current_line);
}