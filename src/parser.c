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

// passer dans mes commandes pour remplacer le $ et le ~
// remove the "" if there are some, I need to remove the "" here
int ms_parse_command(char *command, t_ms *ms)
{
	char **command_split;

	if (ft_str_split(command, &command_split, FT_CHAR_SPACE))
		return (MEMORY_LACK);
	// TODO : handle that error
	if (command_split == NULL)
	    return (1);
	ms->arg = command_split;
	return (0);
}
