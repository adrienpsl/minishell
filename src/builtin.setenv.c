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

int ms_env_add(char ***env, char *var)
{
	char **env_tmp;

	if (!(env_tmp = ft_strsplit_copy(*env, 0)))
		return (-1);
	ms_env_remove(env_tmp, var);
	if (!(env_tmp = ft_strsplit_add(env_tmp, var, FREE_FIRST)))
		return (-1);
	ft_strsplit_free(env);
	*env = env_tmp;
	return (0);
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
		ms_env_add(&g_env, var);
	else
		ret = ft_put_int(-1, MS_SETENV_FORBIDDEN_CHAR);
	free(var);
	return (ret);
}

