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

#include <minishell.prototypes.h>
#include <ft_printf.h>
#include <minishell.defines.h>
#include <ft_strsplit.h>

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

int ms__unsetenv(char **argv, t_array *env)
{
	int size;

	size = ft_strsplit_count(argv);
	if (2 == size)
		ms__env_remove(env, argv[1]);
	else
		ft_printf(MS__NAME"setenv: wrong arguments number");
	return (0);
}
