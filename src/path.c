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

// je donne un path a cette fonction, et elle va loop dessus et me resortir le resultat ?

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
				ft_strcat(m.buffer, path);
				ft_strcat(m.buffer, "/");
				ft_strcat(m.buffer, dp->d_name);
			}
		}
		closedir(dir);
	}
	else
		return (NULL);
	return (m.buffer[0] ? m.buffer : NULL);
}

char *find_binary(char *binary_name)
{
	char **all_path;
	char *value;
	char *res;

	m.i = 0;
	res = NULL;
	ft_bzero(m.buffer, 4096);
	if (!(value = env_get_value("PATH"))
		|| !(all_path = ft_str_split(value, ":")))
		return (NULL);
	while (all_path[m.i])
	{
		if ((res = search_binary_in_path(all_path[m.i], binary_name)))
			return (res);
		m.i++;
	}
	return (res);
}










