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

void ms__unsetenv(t_array *argv, t_array *env, t_array *null)
{
	(void)null;
	if (
		2 == argv->length
		)
		ms__env_remove(
			env,
			ftarray__at(argv, 1)
		);
	else
		ft_printf(MS__NAME"setenv: wrong arguments number");
}