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

static char *search_in_directory(char *path, char *bin_name, int start_mode)
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
			if (!start_mode && ft_streq(dp->d_name, bin_name))
			{
				name = (char*)1;
				break;
			}
			if (start_mode && ft_str_search$start(dp->d_name, bin_name) > -1)
			{
				name = ft_strdup(dp->d_name);
				break;
			}
		}
		closedir(dir);
	}
	return (name);
}

char *ms_find_binary(char *bin_name, int start_mode)
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
			if (!start_mode &&
				search_in_directory(path_split[i], bin_name, 0))
				path = ft_strjoinby(path_split[i], "/", bin_name, 0);
			if (start_mode)
				path = search_in_directory(path_split[i], bin_name, 1);
			i++;
		}
		ft_strsplit_free(&path_split);
	}
	if (!start_mode && path == NULL)
		ft_printf(MS_NAME": command not found: %s\n", bin_name);
	return (path);
}