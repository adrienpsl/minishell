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

#include <minishell.h>

int		ms__setenv(char **argv, char ***env)
{
	int size;

	size = ft_strsplit_count(argv);
	if (1 == size)
	{
		if (0 < ft_strchr_int(*argv, '='))
			ms__env_add(env, NULL, NULL, *argv);
		else
			ft_printf(MS__NAME"setenv: if one argv, must contain =\n");
	}
	else if (2 == size)
		ms__env_add(env, argv[0], argv[1], NULL);
	else
		ft_printf(MS__NAME"setenv: wrong arguments number\n");
	return (0);
}

int		ms__unsetenv(char **argv, char ***env)
{
	int size;

	size = ft_strsplit_count(argv);
	if (1 == size)
		ms__env_delete(*env, *argv);
	else
		ft_printf(MS__NAME"unsetenv: wrong arguments number\n");
	return (0);
}
