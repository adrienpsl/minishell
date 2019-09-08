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

#include <minishell.stuctures.h>
#include <minishell.prototypes.h>
# include "libft.h"

static int env_option_u(t_array *argv)
{
	char **key;
	char **option;

	ftarray__prev(argv);
	while (
		NULL != (option = ftarray__next(argv))
		&& EXIT_SUCCESS == ft_str_cmp("-u", *option)
		)
	{
		if (
			NULL != (key = ftarray__next(argv))
			)
			ms__env_remove(g_ms.env_option, *key);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int env_option_i(t_array *argv)
{
	char **variable;

	ftarray__prev(argv);
	while (
		NULL != (variable = ftarray__next(argv))
		&& ft_strchr(*variable, '=') > 0
		)
	{
		ms__env_add(g_ms.env_option, NULL, NULL, *variable);
	}
	return (EXIT_SUCCESS);
}

static int clean_and_malloc_env_option(t_array *env)
{
	if (
		NULL != g_ms.env_option
		)
		ftarray__free_func(&g_ms.env_option, ms__func_free_env, NULL);
	return (
		NULL != (g_ms.env_option = ftarray__copy(env)) ?
		EXIT_SUCCESS : EXIT_FAILURE
	);
}

static int handle_options(t_array *argv, t_array *env)
{
	int ret;

	ret = EXIT_FAILURE;
	if (
		OK == clean_and_malloc_env_option(env)
		)
	{
		if (
			OK == ft_str_cmp("-u", ftarray__at(argv, argv->i))
			)
			ret = env_option_u(argv);
		else if (
			OK == ft_str_cmp("-i", ftarray__at(argv, argv->i))
			)
			ret = env_option_i(argv);
		else if (
			ret == EXIT_FAILURE
			)
			ft_printf("usage");
	}
	return (ret);
}

/**
 * @brief
 * @param argv
 * @param env
 * @return success == remain argument,
 */
int ms__env(t_array *argv, t_array *env)
{
	int ret;

	ret = EXIT_SUCCESS;
	if (
		0 < ftarray__remain(argv)
		&& '-' == **(char **)ftarray__current(argv)
		)
		ret = handle_options(argv, env);
	if (
		EXIT_SUCCESS == ret
		&& 0 == ftarray__remain(argv)
		)
	{
		ftarray__func(env, ms__print_env, NULL);
		ret = 0;
	}
	return (ret);
}
