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

#include <ft_array.h>
#include <minishell.prototypes.h>

int ms__env_remove(t_array *env, char *key)
{
	int index;

	index = ftarray__find(env, find_variable, key);
	if (
		index > -1
		)
	{
		ms__func_free_env(ftarray__at(env, index), NULL);
		ftarray__remove(env, index);
		return (0);
	}
	return (1);
}




//int ms__env_add(t_array *env, char *key, char *value, char *var)
//{
//
//}