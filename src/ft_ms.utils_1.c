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

/*
** @brief			- test if searched == data before the '=' of current
**					- current (before '=' ) == searched (before the first '=')
** @param current	where I search
** @param searched	what I search
** @return 1 if match // 0 otherwise
*/
static int ms__find_variable(char *current, void *searched)
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
** @brief will loop on the env and return the corresponding value of the key
*/
char *ms__get_value(char **env, char *key)
{
	int position;
	int index;

	if (env == NULL || key == NULL)
		return (NULL);
	index = ft_strsplit_search(env, ms__find_variable, key);
	if (0 <= index)
	{
		position = ft_strchr_int(env[index], '=');
		if (0 < position)
			return (env[index] + position + 1);
	}
	return (NULL);
}

void ms__env_delete(char **env, char *key)
{
	int position;

	if (0 <= (position = ft_strsplit_search(env, ms__find_variable, key)))
		ft_strsplit_remove(env, position);
}

