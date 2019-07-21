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

static void ms_argv_no_null(char **argv)
{
	static char *builtin[7] = { "cd", "echo", "setenv",
								"unsetenv", "env", "exit", NULL };
	g_ms.argv = argv;
	g_ms.i = ft_str_split_count(g_ms.argv);
	if (ft_streq(*g_ms.argv, "env")
		&& ft_env());
	else if (ft_strsplit_search(builtin, ft_func_split_streq, *argv) > -1)
		ms_handle_builtin(g_ms.argv);
	else
		ms_handle_binary(g_ms.argv);
}

void ms_loop()
{
	char **argv;

	ft_printf("$> ");
	while ((argv = ms_parser_read_command()))
	{
		g_ms.env_tmp = NULL;
		signal(SIGINT, signal_minishell);
		if (*argv != NULL)
			ms_argv_no_null(argv);
		ft_strsplit_free(&argv);
		if (g_ms.env_tmp)
			ft_strsplit_free(&g_ms.env_tmp);
		ft_printf("$> ");
	}
}
