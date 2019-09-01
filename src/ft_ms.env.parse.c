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

#include <minishell.stuctures.h>
#include "libft.h"

t_env_el *ms__fill_env_el(char *key, char *value, int free)
{
	static t_env_el element = { 0 };

	if (NULL == key || NULL == value)
	{
		if (free)
		{
			ftstr__free(&key);
			ftstr__free(&value);
		}
		return (NULL);
	}
	element.value = value;
	element.key = key;
	return (&element);
}

t_env_el *ms__parse_env_variable(char *variable)
{
	int equal_position;

	equal_position = ft_strchr(variable, '=');
	if (
		equal_position <= 0 || '\0' == variable[equal_position + 1]
		)
		return (NULL);
	return (
		ms__fill_env_el(ft_strndup(variable, equal_position),
						ft_strdup(variable + equal_position + 1),
						1
		)
	);
}

t_array *ms__parse_env(char **env_system)
{
	t_array *env;
	t_env_el *element;

	if (
		NULL == (env = ftarray__init(100, sizeof(t_env_el)))
		)
		return (NULL);
	while (NULL != *env_system)
	{
		if (
			(element = ms__parse_env_variable(*env_system))
			)
			ftarray__push(env, element);
		else
			ft_printf("Env add bad arguments: %s\n", *env_system);
		env_system += 1;
	}
	return (env);
}
