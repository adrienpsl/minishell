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

char *find_directory(char *path, char *bin_name, int completion_mode)
{
	DIR *dir;
	struct dirent *dp;
	char *name;

	dir = opendir(path);
	name = NULL;
	if (dir)
	{
		while ((dp = readdir(dir)))
		{
			if (!completion_mode && ft_streq(dp->d_name, bin_name))
			{
				name = (char*)1;
				break;
			}
			if (completion_mode && ft_str_search(dp->d_name, bin_name) > -1)
			{
				name = ft_strdup(dp->d_name);
				break;
			}
		}
		closedir(dir);
	}
	return (name);
}

char *ms_find_binary(char *bin_name, int completion_mode)
{
	char *path;
	char **path_split;
	int i;

	path = NULL;
	if ((path_split = ft_strsplit(ms_get_value("PATH"), ":")))
	{
		i = 0;
		while (path_split[i] && !path)
		{
			if (!completion_mode && find_directory(path_split[i], bin_name, 0))
				path = ft_strjoinby(path_split[i], "/", bin_name, 0);
			if (completion_mode)
				path = find_directory(path_split[i], bin_name, 1);
			i++;
		}
		ft_strsplit_free(&path_split);
	}
	if (!completion_mode && path == NULL)
		ft_printf(MS_NAME": command not found: %s\n", bin_name);
	return (path);
}

int ms_exec_binary(char *path, char **argv, char **env)
{
	pid_t pid;

//	signal(SIGINT, signal_program);
	pid = fork();
	if (pid == 0)
		execve(path, argv, env);
	if (pid > 0)
	{
		wait(&pid);
//		signal(SIGINT, signal_minishell);
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
	if (argv[0][0] == '/')
		path = ft_strdup(*argv);
	else
		path = ms_find_binary(*argv, 0);
	if (!path)
		return (-1);
	if (ms_test_file(MS_NAME, path))
		return (-1);
	return (ms_exec_binary(path, argv, g_env));
}
