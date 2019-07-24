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


static int cd_update_env_print(char *buffer, char *buf_pwd, int *print)
{
	char buf_oldpath[MS_SIZE_BUFFER + 1];

	ft_bzero(buf_oldpath, MS_SIZE_BUFFER + 1);
	ft_strjoinbybuffer(buf_oldpath, "OLDPATH", "=", buf_pwd);
	if (ms_env_add(g_ms.env, buf_oldpath))
	{
		return (-1);
	}
	if (*print)
	{
		ft_printf("%s\n", buffer);
	}
	return (0);
}

static int cd_test_path(char *buffer, char *buf_pwd)
{
	int right;

	if ((right = ms_test_file(buffer, "cd")))
	{
		return right;
	}
	if (getcwd(buf_pwd, MS_SIZE_BUFFER) == NULL)
		return (ft_put_int(-1, MS_CD_NO_AUTHORIZE));
	if (chdir(buffer))
	{
		ft_printf(MS_CD_NO_AUTHORIZE"\n", g_ms.buffer);
		return (-1);
	}
	return (0);
}

int ms_cd()
{
	char buffer[MS_SIZE_BUFFER_FULL];
	char buffer_tmp[MS_SIZE_BUFFER_FULL];
	int print;

	print = 0;
	ft_bzero(buffer, MS_SIZE_BUFFER_FULL);
	ft_bzero(buffer_tmp, MS_SIZE_BUFFER_FULL);
	if (ft_streq(*g_ms.argv, "--"))
	{
		(g_ms.argv++ && g_ms.argv_size--);
	}
	if (g_ms.argv_size > 2)
	{
		return (ft_put_int(-1, MS_BAD_NB_ARG));
	}
	if (cd_standardize_path(buffer, &print)
		|| cd_test_path(buffer, buffer_tmp)
		|| cd_update_env_print(buffer, buffer_tmp, &print))
		return (-1);
	return (0);
}
