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

	if (key)
	{
		position = ft_strsplit_search(g_env, ms_func_search_var$name, key);
		if (position > -1)
		{
			return (g_env[position] + ft_strchr(g_env[position], '=') + 1);
		}
	}
	ft_printf("The env variable : %s is no set.\n", key);
	return (NULL);
}
