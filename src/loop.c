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
	if (ft_streq(*argv, "cd"))
		ft_cd(argv + 1);
	else if (ft_streq(*argv, "exit"))
		exit(EXIT_SUCCESS);
	else if (ft_streq(*argv, "echo"))
		ft_echo(argv + 1);
	else if (ft_streq(*argv, "setenv"))
		ft_setenv(argv + 1);
	else if (ft_streq(*argv, "unsetenv"))
		ft_unsetenv(argv[1]);
}

void ms_loop()
{
	char **argv;
	static char *builtin[7] = { "cd", "echo", "setenv",
								"unsetenv", "env", "exit", NULL };

	ft_printf("$> ");
	while ((argv = ms_parser_read_command()))
	{
		signal(SIGINT, signal_minishell);
		if (*argv != NULL)
		{
			g_ms.argv = argv;
			if (ft_streq(*g_ms.argv, "env")
				&& ft_env(&g_ms.argv))
				;
			else if (ft_strsplit_search(builtin, ft_func_split_streq, *argv) > -1)
				ms_handle_builtin(g_ms.argv);
			else
				ms_handle_binary(g_ms.argv);
			if (g_ms.env_tmp)
				ft_strsplit_free(&g_ms.env_tmp);
		}
		ft_strsplit_free(&argv);
		ft_printf("$> ");
	}
}
