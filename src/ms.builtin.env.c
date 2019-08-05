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

#include "minishell.h"

static char **ms_env_opt_u(char **argv)
{
	if (argv[1] == NULL)
	{
		ft_printf("env: option requires an argument -- %s\n", *argv + 1);
		return (NULL);
	}
	if (!(g_ms.env_tmp = ft_strsplit_copy(ms_get_env(), 0)))
		return ft_put_ptr(NULL, MS_NO_MEMORY);
	ms_env_remove(g_ms.env_tmp, argv[1]);
	return (argv + 2);
}

static char **ms_env_opt_i(char **argv)
{
	if (!(g_ms.env_tmp = ft_strsplit("", " ")))
		return ft_put_ptr(NULL, MS_NO_MEMORY);
	return (argv + 1);
}

char **ms_env(char **argv)
{
	if (ft_streq("-u", argv[0]))
		argv = ms_env_opt_u(argv);
	else if (ft_streq("-i", argv[0]))
		argv = ms_env_opt_i(argv);
	else if (ft_str_search$start(argv[0], "-") > -1)
	{
		ft_printf("env: option requires an argument -- %s\n", *argv);
		return (NULL);
	}
	if (argv && argv[0] == NULL )
	{
		ft_strsplit_print(ms_get_env(), '\n');
		ft_printf("\n");
		return (NULL);
	}
	return (argv);
}
