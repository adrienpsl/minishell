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

int ms_env_remove(char **env, char *var)
{
	int i;

	i = ft_strsplit_search(env, ms_func_search_var$name, var);
	if (i > -1)
		ft_strsplit_remove(env, i);
	return (0);
}

int ms_unsetenv()
{
	if (g_ms.argv_size != 1)
		return ft_put_int(-1, MS_BAD_NB_ARG);
	ft_bzero(g_ms.buffer, MS_SIZE_BUFFER);
	ft_strjoinbuffer(g_ms.buffer, g_ms.argv[0], "=", 0);
	return (ms_env_remove(g_ms.env, g_ms.buffer));
}
