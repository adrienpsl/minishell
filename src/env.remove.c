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

static int matched_env_variable(char *env_key_value, char *searched)
{
	ssize_t i;

	i = ft_str_chr(env_key_value, '=');
	if (i > 0)
		return (!ft_mem_cmp(env_key_value, searched, i));
	return (0);
}

int ms_env_remove(char *removing_var, char ***p_env)
{
	int i;
	char **env;

	i = -1;
	env = *p_env; 
	while (env[++i] != NULL)
	{
		if (matched_env_variable(env[i], removing_var))
		{
			free(env[i]);
			while (env[i] != NULL)
			{
				env[i] = env[i + 1];
				i++;
			}
			return (0);
		}
	}
	return (ft_errno_set(BAD_DELETING_KEY));
}

char *env_get_value(char *key)
{
	int i;
	char **env;

	env = ms.env;
	if (!key)
		return (NULL);
	while (*env != NULL)
	{
		if (matched_env_variable(*env, key))
		{
			i = ft_str_chr(*env, '=');
			if (i == -1)
				return (NULL);
			return ((*env) + i + 1);
		}
		env++;
	}
	return (NULL);
}