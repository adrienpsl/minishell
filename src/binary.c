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

int find_directory(char *path, char *bin_name)
{
	DIR *dir;
	struct dirent *dp;

	dir = opendir(path);
	if (dir)
	{
		while ((dp = readdir(dir)))
		{
			if (ft_streq(dp->d_name, bin_name))
			{
				closedir(dir);
				return (1);
			}
		}
		closedir(dir);
	}
	return (0);
}

char *ms_find_binary(char *bin_name)
{
	char *path;
	char **path_split;
	int i;

	i = 0;
	if (!(path_split = ft_strsplit(ms_get_value("PATH"), ":")))
		return (NULL);
	path = NULL;
	while (path_split[i])
	{
		if (find_directory(path_split[i], bin_name))
		{
			path = ft_strjoinby(path_split[i], "/", bin_name, 0);
			break;
		}
		i++;
	}
	ft_strsplit_free(&path_split);
	return (path);
}

int ms_execute_binary(char *path, char **argv, char **env)
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
	return (0);
}


