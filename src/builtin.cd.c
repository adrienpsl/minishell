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

int cd_go_dir(char *buffer)
{
	int right;
	char b_pwd[MS_SIZE_BUFFER + 1];
	char b_oldpath[MS_SIZE_BUFFER + 1];

	if ((right = ms_test_file(buffer, "cd")))
		return (right);
	getcwd(b_pwd, MS_SIZE_BUFFER);
	if (chdir(buffer))
	{
		ft_printf(MS_CD_NO_AUTHORIZE, g_ms.buffer);
		return (-1);
	}
	ft_bzero(b_oldpath, MS_SIZE_BUFFER + 1);
	ft_strjoinbybuffer(b_oldpath, "OLDPATH", "=", b_pwd);
	if (ms_env_add(g_ms.env, b_oldpath))
		return (-1);
	return (0);
}

int ms_cd()
{
	char buffer[MS_SIZE_BUFFER_FULL];
	int print;

	print = 0;
	ft_bzero(buffer, MS_SIZE_BUFFER_FULL);
	if (ft_streq(*g_ms.argv, "--"))
	{
		(g_ms.argv++ && g_ms.argv_size--);
	}
	if (g_ms.argv_size > 2)
	{
		return (ft_put_int(-1, MS_BAD_NB_ARG));
	}
	if (cd_standardize_path(buffer, &print)
		|| cd_go_dir(buffer))
		return (-1);
	return (0);
}
