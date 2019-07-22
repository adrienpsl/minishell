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

int ms_copy_env(char **dest, char **src)
{
	int ret;
	int i;

	ret = 0;
	if (ft_strsplit_count(src) > MS_SIZE_MAX_ENV)
		ret = ft_put_int(-1, MS_NEW_ENV_TOO_BIG);
	i = 0;
	while (!ret && src[i])
	{
		if (!(dest[i] = ft_strdup(src[i])))
			ret = -1;
		i++;
	}
	return (ret);
}

// test if = or if not ==
//static int ms_env_check_two$argv()
//{
//	
//}
// split buffer add.

int ms_env_add(char **env, char *var)
{
	int ret;
	int i;

	ret = 0;
	i = 0;
	if (ft_strsplit_count(env) + 1 > MS_SIZE_MAX_ENV)
		ret = ft_put_int(-1, MS_NEW_ENV_TOO_BIG);
	while (env[i])
		i++;
	if (!(env[i] = ft_strdup(var)))
		ret = -1;
	return (ret);
}

int search_forbidden()
{
	int ret;

	ret = 0;
	if (ft_strchr(g_ms.buffer, '$') != -1)
		ret = ft_put_int(-1, "No $ in env variable");
	if (ft_strnchr(g_ms.tmp_buffer, '=') != 1)
		ret = ft_put_int(-1, "Too much '='");
	return (ret);
}

int nb_arg_and_buffer()
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


int ms_env_check()
{
	int ret;

	ret = 0;
	if (g_ms.argv_size > 2)
		return ft_put_int(-1, MS_SETENV_NB_ARGV);
	ft_bzero(g_ms.tmp_buffer, MS_SIZE_BUFFER);
	if (nb_arg_and_buffer())
		return (ft_put_int(-1, MS_SETENV_NB_ARGV));
	if (search_forbidden())
	    return (-1);
	ms_env_add(g_ms.env, g_ms.tmp_buffer);
	return (0);
}

int ms_env_remove(char **env, char *var)
{
	int i;
	int ret;

	if (ft_strchr(var, '=') > -1)
		i = ft_strsplit_search(env, ft_func_split_streq, var);
	else
		i = ft_strsplit_search(env, ms_func_search_var$name, var);
	ret = i > -1 ? 0 : 1;
	if (i)
		ft_strsplit_remove(env, i);
	return (ret);
}
