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

int env_option_u(t_array *argv, t_array *env_tmp)
{
	char *key;
	char *option;

	ftarray__prev(argv);
	while (
		NULL != (option = get__argv_next(argv))
		&& OK == ft_str_cmp("-u", option)
		)
	{
		if (NULL != (key = get__argv_next(argv)))
			ms__env_remove(env_tmp, key);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int env_option_i(char **argv, t_array *env_tmp)
{
	int i;

	i = 0;
	while (
		NULL != argv[i]
		&& ft_strchr(argv[i], '=') > 0
		)
	{
		ms__env_add(env_tmp, NULL, NULL, *argv);
		i++;
	}
	return (i);
}

static int clean_and_malloc_env_option(t_array *env)
{
	if (NULL != g_ms.env_option)
		ftarray__free_func(&g_ms.env_option, ms__func_free_env, NULL);
	return (
		!(NULL != (g_ms.env_option = ftarray__copy(env)))
	);
}

static int print_usage()
{
	ft_printf("usage");
	return (-1);
}

/*
**	if option, I need to save free the last env if it exist and, init a new one
**	option -u can fail, but no -i
**	if no options find, I print usage
*/
static int handle_options(t_array *argv)
{

	if (OK == ft_str_cmp("-u", get__argv_at(argv, argv->i)))
	{
		if (OK == env_option_u(argv))
			return (OK);
		else
			return (print_usage());
	}
	else if (OK == ft_str_cmp("-i", get__argv_at(argv, argv->i)))
	{
		return (env_option_i(argv));
	}
	else
		ft_printf("usage");
	return (EXIT_FAILURE);
}

/**
 * @brief
 * @param argv
 * @param env
 * @return success == remain argument,
 */
int ms__env(t_array *argv, t_array *env)
{
	if (0 < ftarray__remain(argv)
		&& '-' == *get__argv_current(argv))
	{
		if (handle_options(argv, env))
			return (EXIT_SUCCESS);
	}
	if (0 == ftarray__remain(argv))
	{
		ftarray__func(get__env(), ms__print_env, NULL);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
