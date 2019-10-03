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

#include <minishell.h>

/*
** @brief			- test if searched == data before the '=' of current
**					- current (before '=' ) == searched (before the first '=')
** @param current	where I search
** @param searched	what I search
** @return 1 if match // 0 otherwise
*/

int		find_variable(char *current, void *searched)
{
	int position;

	if (current == NULL || searched == NULL)
		return (-1);
	position = ft_strchr_int(current, '=');
	if (0 < position)
	{
		if (OK == ft_strncmp(current, searched, position)
			&& ('\0' == ((char *)searched)[position]
				|| '=' == ((char *)searched)[position]))
			return (1);
	}
	return (0);
}

/*
**	loop on the env and return the corresponding value of the key,
**	if match, return a char* in the start of the value
*/

char	*ms__env_get_value(char **env, char *key, int (*func)(char *, void *))
{
	static int position;
	static int index;

	if (env == NULL || key == NULL)
		return (NULL);
	index = ft_strsplit_search((char **)env, func, (char *)key);
	if (0 <= index)
	{
		position = ft_strchr_int((char *)env[index], '=');
		if (0 < position)
			return (env[index] + position + 1);
	}
	return (NULL);
}

/*
**	delete in env the given matched key
*/

void	ms__env_delete(char **env, char *key)
{
	int position;

	if (key == NULL)
		return ;
	if (0 <= (position = ft_strsplit_search(env, find_variable, key)))
		ft_strsplit_remove(env, position);
}

/*
**	add to the given env a new variable,
**	if variable is NULL, join of key and value will be use
*/

void	ms__env_add(char ***env, char *key, char *value, char *variable)
{
	ms__env_delete(*env, variable ? variable : key);
	if (variable == NULL)
	{
		if (key == NULL || value == NULL)
			return ;
		variable = ft_strjoin("=", value, 0);
		variable = ft_strjoin(key, variable, 2);
		ft_strsplit_add(env, variable);
		ftstr__free(&variable);
	}
	else
		ft_strsplit_add(env, variable);
}
