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

#include <dirent.h>
#include "minishell.h"

char *display_dir_content(char *path, char *searched_str)
{
	DIR *dir;
	struct dirent *dp;

	dir = opendir(path);
	if (dir)
	{
		while ((dp = readdir(dir)))
		{
			if (ft_str_search(dp->d_name, searched_str) > -1)
				ft_printf("%s  ", dp->d_name);
			if (*searched_str == 0)
				ft_printf("%s  ", dp->d_name);
		}
		closedir(dir);
	}
	return (NULL);
}

char *search_binary_in_path(char *path, char *name)
{
	DIR *dir;
	struct dirent *dp;

	dir = opendir(path);
	if (dir)
	{
		while ((dp = readdir(dir)))
		{
			if (ft_streq(dp->d_name, name))
			{
				ft_strcat(g_ms.buffer, path);
				ft_strcat(g_ms.buffer, "/");
				ft_strcat(g_ms.buffer, dp->d_name);
			}
		}
		closedir(dir);
	}
	else
		return (NULL);
	return (g_ms.buffer[0] ? g_ms.buffer : NULL);
}

char *ft_find_binary(char *binary_name)
{
	char **all_path;
	char *value;
	char *path;

	g_ms.i = 0;
	path = NULL;
	ft_bzero(g_ms.buffer, 4096);
	if (!(value = ms_env_get_value("PATH", g_ms.env))
		|| !(all_path = ft_str_split(value, ":")))
		return (NULL);
	while (all_path[g_ms.i])
	{
		if ((path = search_binary_in_path(all_path[g_ms.i], binary_name)))
			return (path);
		g_ms.i++;
	}
	return (path);
}










