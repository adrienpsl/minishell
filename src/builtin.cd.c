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

static int go_dir(char *go_path, char *current_path)
{
	if (g_test)
		ft_memcpy(g_test_cd_buffer, go_path, ft_strlen(go_path));
	if (!go_path)
		return (ft_errno_set(INVALID_PATH));
	if (access(go_path, F_OK))
	{
		ft_printf("cd: no such file or directory: %s\n", go_path);
		return (ft_errno_set(ENOENT));
	}
	if (chdir(go_path))
	{
		ft_printf("cd: permission denied: %s\n", go_path);
		return (ft_errno_set(EACCES));
	}
	if (ms_env_modify("OLDPATH", current_path))
		return (-1);
	return (0);
}

static int one_argv(char *argv, char *current_path)
{
	ft_bzero(m.buffer, 4097);
	if (ft_streq(argv, "-"))
		return (go_dir(env_get_value("OLDPATH"), current_path));
	else if (ft_streq(argv, "~"))
		return (go_dir(env_get_value("HOME"), current_path));
	else if (*argv == '.')
	{
		ft_strjoinbybuffer(m.buffer, current_path, "/", argv);
		return (go_dir(m.buffer_array, current_path));
	}
	else
		return (go_dir(argv, current_path));
}

static int two_argv(char *searching, char *replacing, char *current_path)
{
	ft_bzero(m.buffer_array, 4097);
	if (!ft_str_replacebuffer(m.buffer, current_path, searching, replacing))
	{
		ft_printf("cd: string not in pwd: %s\n", searching);
		return (-1);
	}
	return (go_dir(m.buffer_array, current_path));
}

int ft_cd(char **argv)
{
	int nb_argv;
	int ret;
	char buff_current_path[4097];

	nb_argv = ft_str_split_count(argv);
	if (ft_streq(*argv, "--"))
		argv++ && nb_argv--;
	if (getcwd(buff_current_path, 4096) == NULL)
		return (ft_errno_set(EACCES));
	if (nb_argv == 0)
		ret = go_dir(env_get_value("HOME"), buff_current_path);
	else if (nb_argv == 1)
		ret = one_argv(*argv, buff_current_path);
	else if (nb_argv == 2)
		ret = two_argv(*argv, argv[1], buff_current_path);
	else
		ret = ft_errno_set(E2BIG);
	return (ret);
}
