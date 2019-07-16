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

int ft_unsetenv(char *removing_var)
{
	int i;

	i = ft_strsplit_search(m.env, ms_search_function, removing_var);
	if (i > -1)
	{
		free(m.env[i]);
		while (m.env[i] != NULL)
		{
			m.env[i] = m.env[i + 1];
			i++;
		}
		return (0);
	}
	return (-1);
}



void ft_env()
{
	char option = 'i';

	// catch option

	if (option == 'i')
	{
//		char **env = ;
	};
	// argument:
	// -i lance la commande sans env

	// -u lance la commande en changeant l'argument.

	//pas d'argument
	ft_strsplit_print(m.env, '\n');
}