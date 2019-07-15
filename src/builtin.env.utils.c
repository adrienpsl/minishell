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
	if (!(m.env = ft_str_split_copy(env, 0)))
		return (-1);
	return (0);
}

int ms_env_modify(char *key, char *new_value)
{
	static char *split[3] = { NULL, NULL, NULL };

	ft_unsetenv(key);
	split[0] = key;
	split[1] = new_value;
	return (ft_setenv(split));
}

int ms_matched_env_variable(char *env_key_value, char *searched)
{
	ssize_t i;

	i = ft_strchr(env_key_value, '=');
	if (i > 0)
		return (ft_strneq(env_key_value, searched, i));
	return (0);
}

char *ms_env_get_value(char *key)
{
	int i;
	char **env;

	env = m.env;
	if (!key)
		return (NULL);
	while (*env != NULL)
	{
		if (ms_matched_env_variable(*env, key))
		{
			i = ft_strchr(*env, '=');
			if (i == -1)
				return (NULL);
			return ((*env) + i + 1);
		}
		env++;
	}
	return (NULL);
}