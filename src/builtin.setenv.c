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

char **ms_env_add(char **src, char *var, int do_free)
{
	char **new_env;

	if (!(new_env = ft_strsplit_copy(src, 0)))
		return (NULL);
	ms_env_remove(new_env, var);
	return (ft_strsplit_add(new_env, var, do_free));
}

int ms_setenv(char **argv)
{
	int size;
	char *var;
	int ret;

	ret = 0;
	size = ft_strsplit_count(argv);
	if (size > 2 || size == 0)
		return ft_put_int(-1, MS_BAD_NB_ARG);
	var = (size == 2) ?
		  ft_strjoinby(argv[0], "=", argv[1], 0) :
		  ft_strdup(argv[0]);
	if (!var)
		return (ft_put_int(-1, MS_NO_MEMORY));
	if (ft_strchr(var, '$') == -1 && ft_strnchr(var, '=') == 1)
		g_ms.env = ms_env_add(g_ms.env, var, FREE);
	else
		ret = ft_put_int(-1, MS_SETENV_FORBIDDEN_CHAR);
	free(var);
	return (ret);
}

