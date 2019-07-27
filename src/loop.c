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

void ms_handle_builtin(char **argv)
{
	//	if (ft_streq(*argv, "cd"))
	//		ft_cd(argv + 1);
	if (ft_streq(*argv, "exit"))
		exit(EXIT_SUCCESS);
	else if (ft_streq(*argv, "echo"))
		ft_echo(argv + 1);
	//	else if (ft_streq(*argv, "setenv"))
	//		ft_setenv(argv + 1);
	//	else if (ft_streq(*argv, "unsetenv"))
	//		ms_unsetenv(0);
}

void ms_loop()
{
	char **argv;
	char **real_env;

	real_env = NULL;
	ft_printf("$> ");
	while (ms_parser(&argv))
	{
		signal(SIGINT, signal_minishell);
		if (*argv != NULL)
		{
			if (ft_streq(*argv, "env"))
				ms_env(argv, &real_env);
			// lance l'option
		}
		if (real_env)
		{
			ft_strsplit_free(&g_env);
			g_env = real_env;
			real_env = NULL;
		}
		ft_strsplit_free(&argv);
		ft_printf("$> ");
	}
}
