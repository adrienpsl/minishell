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
#include <minishell.stuctures.h>
#include <ft_str.h>
#include <ft_printf.h>

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
	return (-1);
}


static int add_to_env(t_array *env, t_env_el *element)
{
	if (
		NULL != element
		)
	{
		ms__env_remove(env, element->key);
		return (
			ftarray__push(env, element)
		);
	}
	else
		return (
			-1
		);
}

int ms__env_add(t_array *env, char *key, char *value, char *variable)
{
	if (
		NULL != variable
		)
	{
		return (
			add_to_env(env,
					   ms__parse_env_variable(variable, 1)
			)
		);
	}
	else
	{
		return (
			add_to_env(env,
					   ms__fill_env_el(
						   ft_strdup(key),
						   ft_strdup(value), 1)
			)
		);
	}
}