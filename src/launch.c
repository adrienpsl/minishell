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

int ms_ex_binary(char *path, char **argv, char **env)
{
	pid_t pid;

	signal(SIGINT, signal_program);

	pid = fork();
	if (pid == 0)
	{
		execve(path, argv, env);
	}
	if (pid > 0)
	{
		wait(&pid);
		signal(SIGINT, signal_minishell);
	}
	//	if (pid < 0); // TODO : handle errors.
	return (0);
}

void ms_do_builtin(char **argv)
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

int ms_do_cmd(char **argv)
{
	static char *builtin[7] = { "cd", "echo", "setenv",
								"unsetenv", "env", "exit", NULL };
	char *path;

	if (ft_strsplit_search(builtin, ft_func_split_streq, *argv) > -1)
		ms_do_builtin(argv);
	else
	{
		if (*argv[0] == '/' && !ms_test_file(*argv, "mimishell"))
			path = *argv;
		else
			path = ft_find_binary(*argv);
		if (path)
			ms_ex_binary(path, argv, g_ms.env_tmp ? g_ms.env : g_ms.env_tmp);
		else
		{
			ft_printf("no such binary\n");
			return (-1);
		}
	}
	return (0);
}

void ms_loop()
{
	char **argv;

	ft_printf("$> ");
	while ((argv = read_command()) && !g_mst.end_test)
	{
		signal(SIGINT, signal_minishell);
		if (*argv == NULL)
			(void) 1; // print truc
		else
			ms_do_cmd(argv);
		ft_str_split_free(&argv);
		ft_printf("$> ");
	}
}
