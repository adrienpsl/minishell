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

int ms_exec_binary(char *path, char **argv, char **env)
{
	pid_t pid;

	pid = fork();
	//	signal(SIGINT, ms_signal_exec);
	if (pid == 0)
		if (-1 == execve(path, argv, env))
			return (-1);
	if (pid > 0)
		wait(&pid);
	if (pid < 0)
		return (-1);
	//	signal(SIGINT, ms_signal_minishell);
	return (OK);
}

char *find_binary_path(char *name, t_array *env, t_s *buffer)
{
	if (name[0] != '/')
	{
		ms__find_binary(env, name, buffer, MS__FIND_BINARY_SEARCH);
		if ('\0' == buffer->data[0])
		{
			ft_printf(MS__NAME" command not found: %s\n", name);
			return (NULL);
		}
		else
		{
			if (OK == ft_exist_and_right_file(buffer->data, MS__NAME, name))
				return (ft_strdup(buffer->data));
			else
				return (NULL);
		}
	}
	else
	{
		if (OK == ft_exist_and_right_file(name, MS__NAME, name))
			return (ft_strdup(name));
		else
			return (NULL);
	}
}

int ms__exec(char **argv, t_array *env, t_s *buffer)
{
	char **split_env;
	char *path;
	(void)argv;
	(void)path;

	int ret;
	(void)ret;

	//	if ();
	split_env = ms__convert_env(env, buffer);
	//	if (NULL != path && '\0' != *path
	//		&& NULL != split_env)
	//		ret = ms_exec_binary(path, argv, split_env);
	//	else
	//		ret = -1;
	ft_strsplit_free(&split_env);
	//	ftstr__free(&path);
	//	return (ret);
	return (0);
}

// il me faut une fonction pour tester les files
// et savoir quelle est le pb.