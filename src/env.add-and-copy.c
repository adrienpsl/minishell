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
	if (!(ms.env = ft_str_split_copy(env, 0)))
		return (-1);
	return (0);
}

int ms_env_add(char **argv)
{
	int i;
	char *tmp_str;

	i = ft_str_split_count(argv);
	if (i == 0 || i > 2)
		return (ft_putstrret("Bad number argument given to set env", -1));
	else if (i == 1)
	{
		if (ft_strnchr(*argv, '=') != 1)
			return (ft_putstrret("The env separator is one single =", -1));
		if (!(tmp_str = ft_strdup(*argv)))
			return (-1);
	}
	else
	{
		if (ft_strchr(argv[0], '=') != -1 || ft_strchr(argv[1], '=') != -1)
			return (ft_putstrret("If two elements are supply no =", -1));
		if (!(tmp_str = ft_strjoinby(argv[0], "=", argv[1])))
			return (-1);
	}
	if (!(ms.env = ft_str_split_add(ms.env, tmp_str, 1)))
		return (-1);
	return (0);
}

int ms_env_modify(char *key, char *new_value)
{
	static char *split[3] = { NULL, NULL, NULL };

	ms_env_remove(key);
	split[0] = key;
	split[1] = new_value;
	if (ms_env_add(split))
		return (-1);
	return (0);
}