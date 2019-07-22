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

static int one_argument(char *argv)
{
	int ret;
	ssize_t length_var;

	ret = 0;
	if (ft_strchr(argv, '$') != -1)
		ret = ft_put_int(-1, "No $ en env variable");
	else if ((length_var = ft_strnchr(argv, '=')) != 1)
		ret = ft_put_int(-1, "The env separator is one single =");
	else if (length_var > MS_LENGTH_MAX_ENV_VAR)
		ret = ft_put_int(-1,
						 "The max size env length is "MS_LENGTH_MAX_ENV_VAR_STR);
	else
		ft_strcat(g_ms.buffer, argv);
	return (ret);
}

static int two_arguments(char **argv)
{
	int ret;

	ret = 0;
	if (ft_strchr(argv[0], '$') != -1
		|| ft_strchr(argv[1], '$') != -1)
		ret = ft_put_int(-1, "No $ en env variable");
	else if (ft_strchr(argv[0], '=') != -1
			 || ft_strchr(argv[1], '=') != -1)
		ret = ft_put_int(-1, "If there is two element, supply no =");
	else if (ft_strlen(argv[0]) > MS_LENGTH_MAX_ENV_VAR)
		ret = ft_put_int(-1,
						 "The max size env length is "MS_LENGTH_MAX_ENV_VAR_STR);
	else
		ft_strjoinbybuffer(g_ms.buffer, argv[0], "=", argv[1]);
	return (ret);
}

// if there is an old path, I need to delete it
// c'est relou ca aussi, je ferai bien un env de max 100 value et pas plus.
// avec un autre max de
//static int ms_set_env_remove$last(char ***env)
//{
//	char **new_env;
//	char var_name_buffer[MS_LENGTH_MAX_ENV_VAR + 1];
//
//	ft_bzero(var_name_buffer, MS_LENGTH_MAX_ENV_VAR + 1);
//	ft_memcpy(var_name_buffer, g_ms.buffer, ft_strchr(g_ms.buffer, '='));
//}

char **ms_set_env(char **argv, char **env)
{
	int i;
	int ret;
	char **nev_env;

	i = ft_strsplit_count(argv);
	nev_env = NULL;
	ms_clear_buffer();

	if (i == 1)
		ret = one_argument(*argv);
	else if (i == 2)
		ret = two_arguments(argv);
	else
		ret = ft_put_int(-1, "Bad number argument given to set env");
	if (ret && !(nev_env = ft_strsplit_add(env, g_ms.buffer, 0)))
		return (NULL);
	return (nev_env);
}

int ft_setenv(char **env)
{
	char **new_env;

	if (!env)
		return (-1);
	if ((new_env = ms_set_env(env, g_ms.env)))
	{
		ft_strsplit_free(&g_ms.env);
		g_ms.env = new_env;
		return (0);
	}
	else
		return (-1);
}

