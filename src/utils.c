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

#include <libft.h>

static int ms__find_variable(char *current, void *searched)
{
	int position;

	position = ft_strchr(current, '=');
	if (0 < position)
	{
		if (OK == ft_strncmp(current, searched, position)
			&& '\0' == ((char *)searched)[position])
			return (1);
	}
	return (0);
}

/*
** @brief loop on the env and return fresh value if match.
*/
char *ms__get_value(char **env, char *key)
{
	int position;
	int index;

	index = ft_strsplit_search(env, ms__find_variable, key);
	if (0 <= index)
	{
		position = ft_strchr(env[index], '=');
		if (0 < position)
			return (ft_strdup(env[index] + position + 1));
	}
	return (NULL);
}

void ms__env_delete(char **env, char *key)
{
	int position;

	if (0 <= (position = ft_strsplit_search(env, ms__find_variable, key)))
		ft_strsplit_remove(env, position);
}

void ms__env_add(char ***env, char *key, char *value)
{
	char *variable;
	char **env_tmp;

	if (NULL == env || NULL == key || NULL == value)
		return ;
	ms__env_delete(*env, key);
	if (NULL == (variable = ft_strjoin("=", value, 0))
		|| NULL == (variable = ft_strjoin(key, variable, 2)))
		return;
	if (NULL == (env_tmp = ft_strsplit_add(*env, variable, 0)))
		return;
	ft_strsplit_free(env);
	*env = env_tmp;
	ftstr__free(&variable);
}

