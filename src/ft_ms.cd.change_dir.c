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

#include <minishell.prototypes.h>

static int test_and_go_dir(char *path, char *argv)
{
	if (OK != ftsystm__test_file(path, "cd", argv))
		return (-1);
	if (OK == chdir(path))
		return (OK);
	else
	{
		ft_printf("cd: not a directory: %s\n", argv);
		return (-1);
	}
}

static char *add_current_path(char *path)
{
	char *full_path;

	full_path = ft_strjoin("/", path, 0);
	full_path = ft_strjoin(ftsystm__get_current_path(), full_path, 2);
	return (full_path);
}

// get fresh path str, and need to clean it.
int cd__change_directory(char *path, char *argv, int print)
{
	int ret;
	char *full_path;

	full_path = (NULL != path
				 && '/' != path[0]) ? add_current_path(path) : ft_strdup(path);
	if (NULL != full_path)
	{
		ret = test_and_go_dir(path, argv);
		if (OK == ret && TRUE == print)
			ft_printf("%s\n", ftsystm__get_current_path());
		ftstr__free(&path);
		ftstr__free(&full_path);
		return (ret);
	}
	ftstr__free(&path);
	return (-1);
}
