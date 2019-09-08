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

#include <minishell.stuctures.h>
#include <minishell.prototypes.h>
#include <ft_printf.h>
#include <minishell.defines.h>
#include <dirent.h>
#include <ft_str.h>

static int search_in_directory(
	char *path,
	char *bin_name,
	int param,
	t_s *buffer
)
{
	DIR *dir;
	struct dirent *dp;

	dir = opendir(path);
	if (dir)
	{
		while (
			(dp = readdir(dir))
			)
		{
			if (
				ftstr__search_start(bin_name, dp->d_name, param) > -1
				)
			{
				fts__add(buffer, dp->d_name);
				closedir(dir);
				return (1);
			}
		}
		closedir(dir);
	}
	return (0);
}

static int
search_path(char *binary_name, char *directory_path, t_s *buffer, int mode)
{
	(void)binary_name;
	fts__clear(buffer);
	if (
		MS__FIND_BINARY_SEARCH == mode
		)
	{
		fts__add(buffer, directory_path);
		fts__add(buffer, "/");
	}
	if (
		search_in_directory(directory_path,
							binary_name,
							MS__FIND_BINARY_COMPLETION == mode ?
							FTSTR__SEARCH_START_PARTIAL :
							FTSTR__SEARCH_START_STRICT,
							buffer)
		)
		return (1);
	else
	{
		fts__clear(buffer);
		return (0);
	}
}

static int init(t_array *env, char **path_str, t_array **paths)
{
	if (
		'\0' == (*path_str = ms__find_env_key(env, "PATH"))[0]
		|| NULL == (*paths = ms__parse_str(*path_str, ":"))
		)
	{
		ft_printf(MS__NAME"no env PATH\n");
		return (
			-1
		);
	}
	ftarray__set_start(*paths);
	return (
		0
	);
}

char *ms__find_binary(t_array *env, char *binary_name, t_s *buffer, int mode)
{
	t_array *paths;
	char *path_str;
	char **directory;

	if (
		init(env, &path_str, &paths)
		)
		return (NULL);
	while (
		(directory = ftarray__next(paths))
		)
	{
		if (
			search_path(binary_name, *directory, buffer, mode)
			)
			break;
	}
	ftarray__free_func(&paths, ftarray__free_func_str, NULL);
	return (
		buffer->data[0] ?
		buffer->data : NULL
	);
}