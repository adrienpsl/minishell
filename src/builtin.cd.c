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

int cd_go_dir()
{
	int right;
	char buffer[MS_SIZE_BUFFER + 1];

	if ((right = ms_test_file(g_ms.buffer, "cd")))
		return (right);
	getcwd(g_ms.tmp_buffer, MS_SIZE_BUFFER);
	if (chdir(g_ms.buffer))
	{
		ft_printf(MS_CD_NO_AUTHORIZE, g_ms.buffer);
		return (-1);
	}
	ft_bzero(buffer, MS_SIZE_BUFFER + 1);
	ft_strjoinbybuffer(buffer, "OLDPATH", "=", g_ms.tmp_buffer);
	if (ms_env_add(g_ms.env, buffer))
		return (-1);
	return (0);
}

int cd_build_path()
{
	if (g_ms.argv_size == 0)
	{
		if (ms_env_get_value("HOME", g_ms.buffer))
			return (ft_put_int(-1, MS_CD_NO_HOME));
	}
	if (g_ms.argv_size == 1)
	{
		if (ft_streq(*g_ms.argv, "-"))
		{
			if (ms_env_get_value("OLDPATH", g_ms.tmp_buffer))
				return (ft_put_int(-1, MS_CD_NO_OLDPATH));
		}
		if (ft_strlen(g_ms.tmp_buffer) + ft_strlen(*g_ms.argv) + 1
			> MS_SIZE_BUFFER)
			return (ft_put_int(-1, MS_BUFFER_ERROR));
		else
			ft_strcat(g_ms.buffer, *g_ms.argv);
	}
	if (g_ms.argv_size == 2)
	{
		if (!ft_str_replacebuffer(g_ms.buffer, g_ms.tmp_buffer,
								  g_ms.argv[1], g_ms.argv[0]))
			return (ft_putval_int(-1, MS_CD_NO_IN_PWD, g_ms.argv[1]));
	}
	return (0);
}

static int cd_check_init()
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

int ms_cd()
{
	if (cd_check_init()
		|| cd_build_path()
		|| cd_go_dir()
	 )
		return (-1);
	return (0);
}
