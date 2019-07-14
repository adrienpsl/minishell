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

	i = ft_strchr(env_key_value, '=');
	if (i > 0)
		return (ft_strneq(env_key_value, searched, i));
	return (0);
}

int ms_env_remove(char *removing_var)
{
	int i;

	i = -1;
	while (m.env[++i] != NULL)
	{
		if (matched_env_variable(m.env[i], removing_var))
		{
			free(m.env[i]);
			while (m.env[i] != NULL)
			{
				m.env[i] = m.env[i + 1];
				i++;
			}
			return (0);
		}
	}
	return (-1);
}

char *env_get_value(char *key)
{
	int i;
	char **env;

	env = m.env;
	if (!key)
		return (NULL);
	while (*env != NULL)
	{
		if (matched_env_variable(*env, key))
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