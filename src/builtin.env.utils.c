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

int ms_search_function(char *current, void *p_searched)
{
	char *searched;
	int i;

	searched = p_searched;
	i = ft_strchr(current, '=');
	if (i > 0)
		return (ft_strneq(current, searched, i));
	return (0);
}

char *ms_env_get_value(char *key, char **argv)
{
	int i;
	int position;

	if (!key)
		return (NULL);
	position = ft_strsplit_search(argv, ms_search_function, key);
	if (position > -1)
	{
		if (!(i = ft_strchr(argv[position], '=')))
			return (NULL);
		return (argv[position] + i + 1);
	}
	return (NULL);
}