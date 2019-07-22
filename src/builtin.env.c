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

static int ms_env_init(long *options)
{
	int ret;

	ret = 0;
	if (g_ms.i && **g_ms.argv == '-')
	{
		if (ft_io_catch_options((*g_ms.argv) + 1, "iu", options))
			ret = ft_put_int(-1, MS_CD_ENV_BAD_OPTION);
		if (g_ms.i == 1)
			ret = ft_put_int(-1, MS_CD_ENV_NO_ARGV);
		g_ms.argv++;
	}
	return ret;
}

static int ft_env_handle_option(long options)
{
	int ret;

	ret = 0;
	if (options & OPTION_U)
	{
		if (ms_copy_env(g_ms.env_tmp, g_ms.env))
		    ret = ft_put_int(-1, MS_NO_MEMORY);
		if (ms_env_remove(g_ms.env, *g_ms.argv) == -1)
			return (-1);
		(g_ms.argv)++;
	}
	if (options & OPTION_I)
	{
		if (!(g_ms.env_tmp = ft_strsplit("", " ")))
			return (-1);
	}
	return (0);
}

int ft_env()
{
	long options;

	g_ms.argv++;
	g_ms.i--;
	options = 0;
	if (ms_env_init(&options))
		return (-1);
	if (ft_env_handle_option(options))
		return (-1);
	if (!*g_ms.env)
	{
		ft_strsplit_print(g_ms.env, '\n');
		ft_printf("\n");
		return (1);
	}
	return (0);
}
