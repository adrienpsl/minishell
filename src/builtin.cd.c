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
		ft_printf(MS_CD_NO_AUTHORIZE, go_path);
		return (-1);
	}
	if (ms_env_modify("OLDPATH", current_path))
		return (-1);
	return (0);
}

static int one_argv(char *argv, char *current_path)
{
	if (ft_streq(argv, "-"))
		return (go_dir(ms_env_get_value("OLDPATH"), current_path));
	else if (*argv == '.')
	{
		ft_strjoinbybuffer(g_ms.buffer, current_path, "/", argv);
		return (go_dir(g_ms.buffer, current_path));
	}
	else
		return (go_dir(argv, current_path));
}

static int ft_cd_check_init()
{
	ft_bzero(g_ms.buffer, MS_SIZE_BUFFER);
	if (ft_streq(*g_ms.argv, "--"))
	{
		(g_ms.argv++ && g_ms.argv_size--);
	}
	if (getcwd(g_ms.tmp_buffer, MS_SIZE_BUFFER) == NULL)
	{
		return (ft_put_int(-1, MS_CD_NO_AUTHORIZE));
	}
	if (g_ms.argv_size > 2)
	{
		return (ft_put_int(-1, MS_BAD_NB_ARG));
	}
	return (0);
}

static int ft_cd_build_path()
{
	int ret;

	ret = 0;
	if (g_ms.argv_size == 0)
	{
		// if pas de home, je return and says ! fuck mam ! no fucking home !
	}
	if (g_ms.argv_size == 2)
	{
		if (!ft_str_replacebuffer(g_ms.buffer, g_ms.tmp_buffer,
								  g_ms.argv[1], g_ms.argv[0]))
			ret = ft_putval_int(-1, MS_CD_NO_IN_PWD, g_ms.argv[1]);
	}
	return (ret);
}

int ft_cd()
{
	ft_cd_check_init();

	if (g_ms.argv_size == 0)
		//		ret = go_dir(ms_env_get_value("HOME", g_ms.env_tmp ? g_ms.env_tmp : g_ms.env), buff_current_path);
		//	else if (nb_argv == 1)
		//		ret = one_argv(*argv, buff_current_path);
		//	else if (nb_argv == 2)
		//		ret = two_argv(*argv, argv[1], buff_current_path);
		//	else
		//		ret = ft_put_int(-1, "cd: too many arguments");
		return (0);
}
