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

char **ms_unset_env(char *removing_var, char **env)
{
	int i;
	char **new_env;

	i = ft_strsplit_search(env, ms_search_function, removing_var);
	if (i > -1)
	{
		if (!(new_env = ft_str_split_copy(env, 0)))
			return (NULL);
		free(new_env[i]);
		while (new_env[i] != NULL)
		{
			new_env[i] = new_env[i + 1];
			i++;
		}
		return (new_env);
	}
	return (NULL);
}

int ft_unsetenv(char *removing_var)
{
	char **new_env;

	new_env = ms_unset_env(removing_var, m.env);
	if (new_env)
	{
		ft_str_split_free(&m.env);
		m.env = new_env;
		return (0);
	}
	return (-1);
}

