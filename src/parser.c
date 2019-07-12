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
	return (current_quote ? 1 : 0);
}

char *get_all_commands()
{
	char *current_line;
	char *tmp;

	if (get_next_line(g_fd, &current_line, 0) == -1)
		return (NULL);
	while (!is_quote_paired(current_line))
	{
		tmp = current_line;
		if (get_next_line(g_fd, &current_line, 0) == -1)
			return (NULL);
		if (!(current_line = ft_strjoin(current_line, tmp, FREE_STR)))
			return (NULL);
	}
	return (current_line);
}
//
//int get_argv()
//{
//	// I check if my line has the " in good order
//	while ()
//	{;
//	}
//}


// passer dans mes commandes pour remplacer le $ et le ~
// remove the "" if there are some, I need to remove the "" here
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
