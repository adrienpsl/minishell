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

int ms_copy_env(char **dest, char **src)
{
	int ret;
	int i;

	ret = 0;
	if (ft_str_split_count(src) > MS_SIZE_MAX_ENV)
		ret = ft_put_int(-1, MS_NEW_ENV_TOO_BIG);
	i = 0;
	while (!ret && src[i])
	{
		if (!(dest[i] = ft_strdup(src[i])))
			ret = -1;
		i++;
	}
	return (ret);
}

int ms_env_add(char **env, char *var)
{
	int ret;
	int i;

	ret = 0;
	i = 0;
	if (ft_str_split_count(env) + 1 > MS_SIZE_MAX_ENV)
		ret = ft_put_int(-1, MS_NEW_ENV_TOO_BIG);
	while (env[i])
		i++;
	if (!(env[i] = ft_strdup(var)))
		ret = -1;
	return (ret);
}

int ms_env_remove(char **env, char *var)
{
	int i;
	int ret;

	if (ft_strchr(var, '=') > -1)
		i = ft_strsplit_search(env, ft_func_split_streq, var);
	else
		i = ft_strsplit_search(env, ms_func_search_var$name, var);
	ret = i > -1 ? 0 : 1;
	if (i)
		ft_strsplit_remove(env, i);
	return (ret);
}
