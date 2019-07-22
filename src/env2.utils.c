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
	if (ft_strsplit_count(src) >= MS_SIZE_MAX_ENV)
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

int ms_env_remove(char **env, char *var)
{
	int i;

	i = ft_strsplit_search(env, ms_func_search_var$name, var);
	if (i > -1)
		ft_strsplit_remove(env, i);
	return (i > -1 ? 1 : 0);
}
