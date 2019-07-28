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

char **ms_env_opt_u(char **argv, char ***real_env)
{
	char **tmp_env;

	if (argv[1] == NULL)
	{
		ft_printf("env: option requires an argument -- %s\n", *argv + 1);
		return (NULL);
	}
	if (!(tmp_env = ft_strsplit_copy(g_env, 0)))
		return ft_put_ptr(NULL, MS_NO_MEMORY);
	ms_env_remove(tmp_env, argv[1]);
	*real_env = g_env;
	g_env = tmp_env;
	return (argv + 2);
}

char **ms_env_opt_i(char **argv, char ***real_env)
{
	char **tmp_env;

	if (!(tmp_env = ft_strsplit("", " ")))
		return ft_put_ptr(NULL, MS_NO_MEMORY);
	*real_env = g_env;
	g_env = tmp_env;
	return (argv + 1);
}

char **ms_env(char **argv, char ***real_env)
{
	if (ft_streq("-u", argv[0]))
		argv = ms_env_opt_u(argv, real_env);
	else if (ft_streq("-i", argv[0]))
		argv = ms_env_opt_i(argv, real_env);
	else if (argv[0] && argv[0][0] == '-')
	{
		ft_printf("env: option requires an argument -- %s\n", *argv + 1);
		return (NULL);
	}
	if (argv && !*argv)
	{
		ft_strsplit_print(g_env, '\n');
		ft_printf("\n");
		return (NULL);
	}
	return (argv);
}
