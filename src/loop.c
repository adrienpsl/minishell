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
	else if (ft_streq(*argv, "env"))
		ft_env(argv + 1);
	else if (ft_streq(*argv, "unsetenv"))
		ft_unsetenv(argv[1]);
}


void ms_loop()
{
	char **argv;
	static char *builtin[7] = { "cd", "echo", "setenv",
								"unsetenv", "env", "exit", NULL };

	ft_printf("$> ");
	while ((argv = read_command()) && !g_mst.end_test)
	{
		signal(SIGINT, signal_minishell);
		if (*argv != NULL)
		{
//			if ()
//			    ;
			if (ft_strsplit_search(builtin, ft_func_split_streq, *argv) > -1)
				ms_handle_builtin(argv);
			else
				ms_handle_binary(argv);
			// clean env if need
		}
		ft_str_split_free(&argv);
		ft_printf("$> ");
	}
}
