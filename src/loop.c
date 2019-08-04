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
			return (func[i].f(argv + 1));
	}
	return (ms_handle_binary(argv));
}

void ms_loop()
{
	char **argv;
	char **real_env;

	real_env = NULL;
	while (42)
	{
		argv = ms_parser();
		if (argv && *argv != NULL)
		{
			if (ft_streq(*argv, "env"))
				ms_send_good(ms_env(argv + 1));
			else
				ms_send_good(argv);
		}
		if (g_ms.env_tmp)
			ft_strsplit_free(&g_ms.env_tmp);
		if (argv)
			ms_print_prompt();
		ft_strsplit_free(&argv);
	}
}
