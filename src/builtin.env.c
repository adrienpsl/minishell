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

static int ft_env_init(char ***argv, long *options, int *i)
{
	*i = ft_str_split_count(*argv);
	*options = 0;
	if (*i && ***argv == '-')
	{
		if (ft_io_catch_options((**argv) + 1, "iu", options))
		{
			ft_printf("env: bad option given ! \n");
			return (-1);
		}
		if (*i == 1)
		{
			ft_printf("env: option requires an argument ! \n");
			return (-1);
		}
		(*argv)++;
	}
	return (0);
}

static int ft_env_handle_option(long options, char ***argv)
{
	if (options & OPTION_U)
	{
		if (ms_unset_env(**argv, g_ms.env, &g_ms.env_tmp) == -1)
			return (-1);
		(*argv)++;
	}
	if (options & OPTION_I)
	{
		if (!(g_ms.env_tmp = ft_str_split("", " ")))
			return (-1);
	}
	return (0);
}

int ft_env(char ***argv)
{
	int i;
	long options;

	g_ms.env_tmp = NULL;
	(*argv)++;
	if (ft_env_init(argv, &options, &i))
		return (-1);
	if (ft_env_handle_option(options, argv))
		return (-1);
	if (!**argv)
	{
		ft_strsplit_print(g_ms.env, '\n');
		ft_printf("\n");
		return (1);
	}
	return (0);
}
