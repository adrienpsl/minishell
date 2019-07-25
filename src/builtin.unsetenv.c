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

int ms_env_remove(char **env, char *var)
{
	int i;

	i = ft_strsplit_search(env, ms_func_search_var$name, var);
	if (i > -1)
		ft_strsplit_remove(env, i);
	return (0);
}

int ms_unsetenv(char **argv, char **env)
{
	int size;

	size = ft_strsplit_count(argv);
	if (size == 1)
		return (ms_env_remove(env, g_ms.argv[0]));
	return (0);
}
