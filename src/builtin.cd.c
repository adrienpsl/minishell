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

int cd_go(char *path)
{
	char buffer[4097];

	if (ms.test)
		ft_mem_copy(ms.testing_str, path, STRING_MODE);
	ft_mem_zero(buffer, 4097);
	if (!path)
		return (ft_errno_set(INVALID_PATH));
	if (access(path, F_OK))
		return (ft_errno_set(ENOENT));
	if (!getcwd(buffer, 4096))
		return (-1);
	if (chdir(path))
		return (ft_errno_set(EACCES));
	if (ms_env_modify("OLDPATH", buffer))
		return (-1);
	return (0);
}

static int cd_one_argv(char *argv, char *curpath)
{
	ft_mem_zero(ms.tmp_buffer, 4097);
	if (ft_str_is(argv, "-"))
		return (cd_go(env_get_value("OLDPATH")));
	if (*argv == '.')
	{
		ft_str_join_by((char **) ms.tmp_buffer, curpath, "/", argv);
		return (cd_go(ms.tmp_buffer));
	}
	return (0);
}

static int cd_two_argv(char *searching, char *replacing, char *curent_path)
{
	ft_mem_zero(ms.tmp_buffer, 4097);
	if (ft_str_replace((char **) &ms.tmp_buffer, curent_path, searching, replacing))
		return (ft_errno_set(STR_NOT_IN_PATH));
	return (cd_go(ms.tmp_buffer));
}

int ms_cd(char **argv)
{
	int nb_argv;
	int ret;
	char buff_path[4097];

	nb_argv = ft_str_split_count(argv);
	if (ft_str_is(*argv, "--"))
		argv++ && nb_argv--;
	if (getcwd(buff_path, 4096) == NULL)
		return (ft_errno_set(EACCES));
	if (nb_argv == 0)
		ret = cd_go(*argv);
	else if (nb_argv == 1)
		ret = cd_one_argv(*argv, buff_path);
	else if (nb_argv == 2)
		ret = cd_two_argv(*argv, argv[1], buff_path);
	else
		ret = ft_errno_set(E2BIG);
	return (ret);
}
