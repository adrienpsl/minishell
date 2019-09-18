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

	return (0 < (position = ft_strchr(current, '='))
			&& OK == ft_strncmp(current, searched, position));
}

/*
** @brief loop on the env and return fresh value if match.
*/
char *ms__get_value(char **env, char *key)
{
	int position;

	if (0 < (position = ft_strsplit_search(env, ms__find_variable, key)))
		return (ft_strdup(env[position]));
	else
		return (NULL);
}

void ms__env_delete(char **env, char *key)
{
	int position;

	if (0 < (position = ft_strsplit_search(env, ms__find_variable, key)))
		ft_strsplit_remove(env, position);
}

void ms__env_add(char ***env, char *key, char *value)
{
	char *variable;
	char **env_tmp;

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

