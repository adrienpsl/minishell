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
#include <minishell.defines.h>

static int add_to_env(t_array *env, t_env_el *element)
{
		if (NULL != element)
	{
		ms__env_remove(env, element->key);
		return (ftarray__push(env, element));
	}
	else
		return (-1);
}

int ms__env_add(t_array *env, char *key, char *value, char *variable)
{
	if (NULL != variable)
	{
		return (
			add_to_env(env, ms__parse_env_variable(variable, 1))
		);
	}
	else
	{
		return (
			add_to_env(env, ms__fill_env_el(
				ft_strdup(key),
				ft_strdup(value), 1))
		);
	}
}

int ms__setenv(t_array *argv, t_array *env)
{
	if (2 == argv->length)
		ms__env_add(
			env,
			NULL,
			NULL,
			ftarray__at(argv, 1));
	else if (3 == argv->length)
		ms__env_add(
			env,
			ftarray__at(argv, 1),
			ftarray__at(argv, 2),
			NULL);
	else
		ft_printf(MS__NAME"setenv: wrong arguments number");
	return (0);
}