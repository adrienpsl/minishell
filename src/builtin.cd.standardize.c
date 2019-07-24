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

#include "minishell.h"

static int standardize_one(char *buffer, int *print)
{
	if (ft_streq(g_ms.argv[0], "-"))
	{
		if (ms_env_get_value("OLDPATH", buffer))
			return (ft_put_int(-1, MS_CD_NO_OLDPATH));
		*print = 1;
	}
	else
	{
		if (ms_put_in_buffer(buffer, g_ms.argv[0]))
			return (-1);
	}
	return (0);
}

static int standardize_two(char *buffer, int *print)
{
	int ret;
	char buf_pwd[MS_SIZE_BUFFER];

	if (getcwd(buf_pwd, MS_SIZE_BUFFER) == NULL)
		return (ft_put_int(-1, MS_CD_NO_AUTHORIZE));
	if ((ft_strlen(g_ms.argv[0]) + ft_strlen(g_ms.argv[1]) + 1)
		> MS_SIZE_BUFFER)
	{
		ret = ft_put_int(-1, MS_BUFFER_ERROR);
	}
	else if (ft_str_replacebuffer(buffer, buf_pwd,
								  g_ms.argv[0], g_ms.argv[1]))
	{
		ret = 0;
		*print = 1;
	}
	else
		ret = (ft_putval_int(-1, MS_CD_NO_IN_PWD, g_ms.argv[1]));
	return (ret);
}

int cd_standardize_relative(char *buffer)
{
	char pwd[MS_SIZE_BUFFER_FULL];

	if (buffer[0] == '.')
	{
		if (getcwd(pwd, MS_SIZE_BUFFER) == NULL)
			return (ft_put_int(-1, MS_CD_NO_AUTHORIZE));
		if ((ft_strlen(pwd) + ft_strlen(g_ms.argv[0]) + 1) > MS_SIZE_BUFFER)
			return (ft_put_int(-1, MS_BUFFER_ERROR));
		ft_strjoinbybuffer(g_ms.buffer, pwd, "/", g_ms.argv[0]);
	}
	return (0);
}

int cd_standardize_path(char *buffer, int *print)
{
	int ret;

	ret = 0;
	if (g_ms.argv_size == 0 && ms_env_get_value("HOME", buffer))
		ret = ft_put_int(-1, MS_CD_NO_HOME);
	if (g_ms.argv_size == 1)
	{
		ret = standardize_one(buffer, print);
	}
	else if (g_ms.argv_size == 2)
	{
		ret = standardize_two(buffer, print);
	}
	if (cd_standardize_relative(buffer))
	{
		ret = -1;
	}
	return (ret);
}

