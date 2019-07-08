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

#include <errno.h>
#include "minishell.h"

/*
 * I had two for have more flexibility for add and delete.
 * */
int ms_env_copy(char **env)
{
	int i;
	char **tmp;

	if (!(tmp = ft_memory(sizeof(char *) * (ft_str_split_count(env) + 2))))
		return (ft_errno_set(ENOMEM));
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_str_dup(&tmp[i], env[i]))
			return (ft_errno_set(ENOMEM));
		i++;
	}
	if (ms.env)
		ft_str_split_free(&ms.env);
	ms.env = tmp;
	return (0);
}

int ms_env_add(char *new_var)
{
	int i;
	char *tmp_str;

	if (!new_var
		|| ft_str_chr(new_var, '=') == -1
		|| ft_str_nchar(new_var, '=') != 1)
		return (ft_errno_set(BAD_VAR));
	i = ft_str_split_count(ms.env);
	if (ft_str_dup(&tmp_str, new_var))
		return (-1);
	ms.env[i] = tmp_str;
	if (ms_env_copy(ms.env))
		return (NO_ENV);
	return (0);
}

int ms_env_modify(char *key, char *new_value)
{
	char *new;
	int ret;

	ret = 0;
	new = NULL;
	if (ms_env_remove(key))
		return (-1);
	if (ft_str_join_by(&new, key, "=", new_value))
		return (-1);
	if (ms_env_add(new))
		ret = -1;
	free(new);
	return (ret);
}