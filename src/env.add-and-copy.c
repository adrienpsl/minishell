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
	if (!(m.env = ft_str_split_copy(env, 0)))
		return (-1);
	return (0);
}



int ms_env_modify(char *key, char *new_value)
{
	static char *split[3] = { NULL, NULL, NULL };

	ms_env_remove(key);
	split[0] = key;
	split[1] = new_value;
	return (ft_setenv(split));
}