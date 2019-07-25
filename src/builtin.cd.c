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

#include <errno.h>
#include "minishell.h"

void cd_print_path(char **argv, char *path_buffer, int i)
{
	char *home;
	char *replace;

	if (i == 2
		|| (i == 1 && argv[0][0] == '-' && !argv[0][1]))
	{
		getcwd(path_buffer, MS_SIZE_BUFFER);
		home = ms_get_value("HOME");
		replace = ft_str_replace(path_buffer, home, "~");
		if (replace)
		{
			ft_printf("%s\n", replace);
			free(replace);
		}
		else
			ft_printf("%s\n", path_buffer);
	}
}

int cd_move_directory(char *path, char *pwd, char **argv)
{
	char *oldpath;

	if (!path || access(path, F_OK))
	{
		ft_printf("cd: no such file or directory: %s\n", *argv);
		return (-1);
	}
	if (access(path, R_OK))
	{
		ft_printf("cd: permission denied: %s\n", *argv);
		return (-1);
	}
	if (chdir(path))
	{
		ft_printf("cd : not a directory: %s\n", argv[0]);
		return (-1);
	}
	if (!(oldpath = ft_strjoinby("OLDPATH", "=", pwd, 0)))
		return (ft_put_int(-1, MS_NO_MEMORY));
	ms_env_add(&g_ms.env, oldpath);
	return (0);
}

char *cd_seriasize_path(char **argv, int size, char *current_pwd)
{
	char *path;

	if (!size)
	{
		if (!(path = ft_strdup(ms_get_value("HOME"))))
			return (NULL);
	}
	else if (size == 2)
	{
		if (!(path = ft_str_replace(current_pwd, argv[0], argv[1])))
			return (ft_put_ptr(NULL, MS_CD_NO_IN_PWD));
	}
	else if (argv[0][0] == '-' && !argv[0][1])
	{
		if (!(path = ft_strdup(ms_get_value("OLDPATH"))))
			return (NULL);
	}
	else
	{
		path = (argv[0][0] == '.') ?
			   ft_strjoinby(current_pwd, "/", argv[0], 0) :
			   ft_strdup(argv[0]);
		if (!path)
			return (ft_put_ptr(NULL, MS_NO_MEMORY));
	}
	return (path);
}

int ms_cd(char **argv)
{
	int size;
	char current_pwd[MS_SIZE_BUFFER_FULL];
	char *path;

	if (ft_streq(*argv, "--"))
		argv++;
	size = ft_strsplit_count(argv);
	getcwd(current_pwd, MS_SIZE_BUFFER_FULL);
	if (size < 2)
	{
		if ((path = cd_seriasize_path(argv, size, current_pwd)))
		{
			if (cd_move_directory(path, current_pwd, argv))
				return (-1);
			cd_print_path(argv, current_pwd, size);
			free(path);
			return (0);
		}
		return (-1);
	}
	else
		return (ft_put_int(-1, MS_BAD_NB_ARG));
}
