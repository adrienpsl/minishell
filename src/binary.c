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

int ms_exec_binary(char *path, char **argv, char **env)
{
	pid_t pid;

	signal(SIGINT, signal_program);
	pid = fork();
	if (pid == 0)
		execve(path, argv, env);
	if (pid > 0)
	{
		wait(&pid);
		signal(SIGINT, signal_minishell);
	}
	if (pid < 0)
		return (ft_put_int(-1, MS_NAME" binary exec fail"));
	free(path);
	return (0);
}

int ms_handle_binary(char **argv)
{
	char *path;
	int size;

	size = ft_strsplit_count(argv);
	if (size == 0)
		return (-1);
	path = argv[0][0] == '/' ?
		   ft_strdup(*argv) :
		   ms_find_binary(*argv, 0);
	if (!path)
		return (-1);
	if (ms_test_file(MS_NAME, path))
		return (-1);
	return (ms_exec_binary(path, argv, ms_get_env()));
}
