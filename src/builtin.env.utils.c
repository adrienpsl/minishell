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

int ms_env_copy(char **env)
{
	if (!(g_ms.env = ft_strsplit_copy(env, 0)))
		return (-1);
	return (0);
}

int ms_func_search_var$name(char *current, void *p_searched)
{
	char *searched;
	int i;

	searched = p_searched;
	i = ft_strchr(current, '=');
	if (i > -1)
		return (ft_strneq(current, searched, i));
	return (0);
}

char *ms_get_value(char *key)
{
	int position;
	char **env;

	if (key)
	{
		env = ms_get_env();
		position = ft_strsplit_search(env, ms_func_search_var$name, key);
		if (position > -1)
		{
			return (env[position] + ft_strchr(env[position], '=') + 1);
		}
	}
	ft_printf("The env variable : %s is no set.\n", key);
	return (NULL);
}
