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

#include <ft_s.h>
#include <minishell.prototypes.h>
#include <minishell.defines.h>
#include "libft.h"

static int ms_exec_binary(char *path, char **argv, char **env)
{
	pid_t pid;

	pid = fork();
	//	signal(SIGINT, ms_signal_exec);
	if (pid == 0)
		execve(path, argv, env);
	if (pid > 0)
		wait(&pid);
	if (pid < 0)
	{
		ft_printf("error binary");
	}
	//	signal(SIGINT, ms_signal_minishell);
	free(path);
	return (0);
}

int ms__exec(char **argv, t_array *env, t_s *buffer)
{
	char **split_env;
	char *path;

	fts__clear(buffer);
	if (argv[0][1] == '/')
		path = ft_strdup(argv[0]);
	else
		path = ft_strdup(
			ms__find_binary(env, argv[0], buffer, MS__FIND_BINARY_SEARCH));
	split_env = ms__convert_env(env, buffer);
	if (NULL != path && NULL != split_env)
	{
		ms_exec_binary(path, argv, split_env);
	}
	ft_strsplit_free(&split_env);
	ftstr__free(&path);
}
