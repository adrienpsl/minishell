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

int ms_send_good(char **argv)
{
	int i;
	static t_n func[5] =
	 {
	  { "cd",       ms_cd },
	  { "exit",     ms_exit },
	  { "echo",     ms_echo },
	  { "setenv",   ms_setenv },
	  { "unsetenv", ms_unsetenv },
	 };

	if (!argv || !*argv)
		return (0);
	i = -1;
	while (++i < 5)
	{
		if (ft_streq(func[i].name, argv[0]))
			return (func[i].f(argv));
	}
	return (ms_handle_binary(argv));
}

void ms_loop()
{
	char **argv;
	char **real_env;

	real_env = NULL;
	ft_printf("$> ");
	while (!ms_parser(&argv))
	{
		signal(SIGINT, signal_minishell);
		if (*argv != NULL)
		{
			if (ft_streq(*argv, "env"))
				ms_send_good(ms_env(argv, &real_env));
			else
			ms_send_good(argv);
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
