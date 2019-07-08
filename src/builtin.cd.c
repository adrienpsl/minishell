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

static int cd_go(char *go_path, char *current_path)
{
	if (ms.test)
		ft_mem_copy(ms.testing_str, go_path, STRING_MODE);
	if (!go_path)
		return (ft_errno_set(INVALID_PATH));
	if (access(go_path, F_OK))
		return (ft_errno_set(ENOENT));
	if (chdir(go_path))
		return (ft_errno_set(EACCES));
	if (ms_env_modify("OLDPATH", current_path))
		return (-1);
	return (0);
}

static int cd_one_argv(char *argv, char *current_path)
{
	ft_mem_zero(ms.tmp_buffer, 4097);
	if (ft_str_is(argv, "-"))
		return (cd_go(env_get_value("OLDPATH"), current_path));
	if (*argv == '.')
	{
		ft_str_join_by((char **) ms.tmp_buffer, current_path, "/", argv);
		return (cd_go(ms.tmp_buffer, current_path));
	}
	return (0);
}

static int cd_two_argv(char *searching, char *replacing, char *current_path)
{
	ft_mem_zero(ms.tmp_buffer, 4097);
	if (ft_str_replace((char **) &ms.tmp_buffer, current_path, searching, replacing))
		return (ft_errno_set(STR_NOT_IN_PATH));
	return (cd_go(ms.tmp_buffer, current_path));
}

int ms_cd(char **argv)
{
	int nb_argv;
	int ret;
	char buff_current_path[4097];

	nb_argv = ft_str_split_count(argv);
	if (ft_str_is(*argv, "--"))
		argv++ && nb_argv--;
	if (getcwd(buff_current_path, 4096) == NULL)
		return (ft_errno_set(EACCES));
	if (nb_argv == 0)
		ret = cd_go(*argv, buff_current_path);
	else if (nb_argv == 1)
		ret = cd_one_argv(*argv, buff_current_path);
	else if (nb_argv == 2)
		ret = cd_two_argv(*argv, argv[1], buff_current_path);
	else
		ret = ft_errno_set(E2BIG);
	return (ret);
}
