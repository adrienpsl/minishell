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
#include <minishell.defines.h>

void ms__env_add(char ***env, char *key, char *value)
{
	char *variable;

	if (NULL == env || NULL == key || NULL == value)
		return;
	ms__env_delete(*env, key);
	if (NULL == (variable = ft_strjoin("=", value, 0))
		|| NULL == (variable = ft_strjoin(key, variable, 2)))
		return;
	if (OK != ft_strsplit_add(env, variable))
		return;
	ftstr__free(&variable);
}

static int one_argument(char **argv, char ***env)
{
	int position;

	if (0 < (position = ft_strchr_int(*argv, '=')))
	{
		(*argv)[position] = '\0';
		ms__env_add(env, *argv, (*argv) + position + 1);
		return (OK);
	}
	else
		return (-1);
}

int ms__setenv(char **argv, char ***env)
{
	int size;

	size = ft_strsplit_count(argv);
	if (1 == size)
	{
		if (OK != one_argument(argv, env))
			ft_printf(MS__NAME"setenv: if one argv, must contain =");
	}
	else if (2 == size)
		ms__env_add(env, argv[0], argv[1]);
	else
		ft_printf(MS__NAME"setenv: wrong arguments number");
	return (0);
}

int ms__unset_env(char **argv, char ***env)
{
	int size;

	size = ft_strsplit_count(argv);
	if (2 == size)
		ms__env_delete(*env, *argv);
	else
		ft_printf(MS__NAME"setenv: wrong arguments number");
	return (0);
}
