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

static void ms_argv_loop(char *command)
{
	char **argv;

	argv = ft_strsplit(command, " ");
	if (argv && argv[0])
	{
		if (ft_streq(argv[0], "env"))
			ms_send_good(ms_env(argv + 1));
		else
			ms_send_good(argv);
		g_ms.env_tmp ? ft_strsplit_free(&g_ms.env_tmp) : 0;
	}
	ft_strsplit_free(&argv);
}

void ms_command_loop()
{
	int i;
	char **commands_split;

	ms_print_prompt();
	while (42)
	{
		i = 0;
		if (!(commands_split = ms_get_commands()))
			return;
		while (commands_split[i])
		{
			if (i)
				ft_putstr_fd("\n", 1);
			ms_argv_loop(commands_split[i]);
			i++;
		}
		ft_strsplit_free(&commands_split);
		ms_print_prompt();
	}
}
