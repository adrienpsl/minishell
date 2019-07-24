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
	char buffer[MS_SIZE_BUFFER + 1];

	ft_bzero(buffer, MS_SIZE_BUFFER + 1);
	ft_strjoinbuffer(buffer, var, "=", 0);
	i = ft_strsplit_search(env, ms_func_search_var$name, var);
	if (i > -1)
		ft_strsplit_remove(env, i);
	return (0);
}

int ms_unsetenv()
{
	if (g_ms.argv_size != 1)
		return ft_put_int(-1, MS_BAD_NB_ARG);
	if (ft_strlen(g_ms.argv[0]) > MS_SIZE_BUFFER)
		return (ft_put_int(-1, MS_BUFFER_ERROR));
	return (ms_env_remove(g_ms.env, g_ms.argv[0]));
}
