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

int ms_env_add(char **env, char *var)
{
	int i;

	i = 0;
	ms_env_remove(env, var);
	if (ft_strsplit_count(env) + 1 >= MS_SIZE_MAX_ENV)
		return (ft_put_int(-1, MS_NEW_ENV_TOO_BIG));
	while (env[i])
		i++;
	if (!(env[i] = ft_strdup(var)))
		return (ft_put_int(-1, MS_NO_MEMORY));
	return (0);
}

static int search_forbidden()
{
	int ret;

	ret = 0;
	if (ft_strchr(g_ms.tmp_buffer, '$') != -1)
		ret = ft_put_int(-1, MS_SETENV_FORBIDDEN_CHAR);
	else if (ft_strnchr(g_ms.tmp_buffer, '=') != 1)
		ret = ft_put_int(-1, MS_SETENV_FORBIDDEN_CHAR);
	return (ret);
}

static int nb_arg_and_buffer()
{
	size_t length;

	length = (g_ms.argv_size == 2) ?
			 ft_strlen(g_ms.argv[0]) + ft_strlen(g_ms.argv[1]) + 1 :
			 ft_strlen(g_ms.argv[0]);
	if (length > MS_MAX_LENGTH_VAR)
		return (-1);
	g_ms.argv_size == 2 ?
	ft_strjoinbybuffer(g_ms.tmp_buffer, g_ms.argv[0], "=", g_ms.argv[1]) :
	ft_memcpy(g_ms.tmp_buffer, g_ms.argv[0], length);
	return (0);
}

int ms_setenv(void)
{
	ft_bzero(g_ms.tmp_buffer, MS_SIZE_BUFFER);
	if (g_ms.argv_size > 2 || g_ms.argv_size == 0)
		return ft_put_int(-1, MS_BAD_NB_ARG);
	if (nb_arg_and_buffer())
		return (ft_put_int(-1, MS_BAD_NB_ARG));
	if (search_forbidden())
		return (-1);
	if (ms_env_add(g_ms.env, g_ms.tmp_buffer))
		return (-1);
	return (0);
}

