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
	int right;

	if (!go_path)
		return (-1);
	if (g_test)
		ft_memcpy(g_mst.buffer, go_path, ft_strlen(go_path));
	if ((right = ms_test_file(go_path, "cd")))
		return (right);
	if (chdir(go_path))
	{
		ft_printf("cd: permission denied: %s\n", go_path);
		return (-1);
	}
	if (ms_env_modify("OLDPATH", current_path))
		return (-1);
	return (0);
}

static int one_argv(char *argv, char *current_path)
{
	ft_bzero(g_ms.buffer, 4097);
	if (ft_streq(argv, "-"))
		return (go_dir(ms_env_get_value("OLDPATH", g_ms.env_tmp ? g_ms.env_tmp : g_ms.env), current_path));
	else if (ft_streq(argv, "~"))
		return (go_dir(ms_env_get_value("HOME", g_ms.env_tmp ? g_ms.env_tmp : g_ms.env), current_path));
	else if (*argv == '.')
	{
		ft_strjoinbybuffer(g_ms.buffer, current_path, "/", argv);
		return (go_dir(g_ms.buffer, current_path));
	}
	else
		return (go_dir(argv, current_path));
}

static int two_argv(char *searching, char *replacing, char *current_path)
{
	ft_bzero(g_ms.buffer, 4097);
	if (!ft_str_replacebuffer(g_ms.buffer, current_path, searching, replacing))
	{
		ft_printf("cd: string not in pwd: %s\n", searching);
		return (-1);
	}
	return (go_dir(g_ms.buffer, current_path));
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
		return (ft_put_int(-1, "No access to current directory"));
	if (nb_argv == 0)
		ret = go_dir(ms_env_get_value("HOME", g_ms.env_tmp ? g_ms.env_tmp : g_ms.env), buff_current_path);
	else if (nb_argv == 1)
		ret = one_argv(*argv, buff_current_path);
	else if (nb_argv == 2)
		ret = two_argv(*argv, argv[1], buff_current_path);
	else
		ret = ft_put_int(-1, "cd: too many arguments");
	return (ret);
}
