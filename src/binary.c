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

 int ms_search_in_directory(
	char *directory_path,
	char *binary_name
)
{
	DIR *dir;
	struct dirent *dp;
	int exist;

	exist = 0;
	dir = opendir(directory_path);
	if (dir)
	{
		while ((dp = readdir(dir)))
		{
			if (ft_streq(dp->d_name, binary_name))
			{
				ft_strcat(g_ms.buffer, directory_path);
				ft_strcat(g_ms.buffer, "/");
				ft_strcat(g_ms.buffer, dp->d_name);
				exist = 1;
			}
		}
		closedir(dir);
	}
	return (exist);
}

//static int ms_loop_on_path_directory(char *binary_name)
//{
//	char **all_path;
//	char *value;
//	int i;
//	int ret;
//
//	i = 0;
//	ret = 0;
//	if (!(value = ms_env_get_value("PATH", g_ms.env)))
//		ret = ft_put_int(-1, MS_NAME ": no PATH in env");
//	if (!(all_path = ft_strsplit(value, ":")))
//		ret = ft_put_int(-1, MS_NAME ": no memory");
//	while (ret == 0 && all_path[i])
//	{
//		if (ms_search_in_directory(all_path[i], binary_name))
//			break;
//		i++;
//	}
//	ft_strsplit_free(&all_path);
//	return (ret);
//}

static int ms_execute_binary(char *path, char **argv, char **env)
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

int ms_handle_binary(char **argv)
{
	char *path;

	ft_bzero(g_ms.buffer, 4096);
	if (*argv[0] != '/')
	{
		if (ft_strlen(*argv) > MS_SIZE_BUFFER)
			return ft_put_int(-1,
							  MS_NAME" : path too long, max size 4096");
//		if (ms_loop_on_path_directory(*argv))
//			return (-1);
		path = g_ms.buffer;
	}
	else
		path = *argv;
	if (ms_test_file("mimishell", path))
		return (-1);
	if (ms_execute_binary(path, argv + 1, g_ms.env_tmp ? g_ms.env_tmp : g_ms.env))
		return (-1);
	return (0);
}

