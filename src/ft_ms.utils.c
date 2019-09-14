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

#include <minishell.stuctures.h>
#include <minishell.prototypes.h>
#include <ft_mem.h>
#include <sys/param.h>
#include "stdlib.h"

int ms__func_free_env(void *element, void *param)
{
	t_env_el *el;
	(void)param;

	el = element;
	free(el->value);
	free(el->key);
	return (0);
}

int ms__init(char **env)
{
	ft_bzero(&g_ms, sizeof(g_ms));
	if (
		NULL == (g_ms.env = ms__parse_env(env))
		|| NULL == (g_ms.buffer = fts__init(200))
		|| NULL == (g_ms.current_line = fts__init(200))
		|| NULL == (g_ms.buffer_cd = fts__init(MAXPATHLEN * 2))
		)
		return (-1);
	else
		return (0);
}

void ms__free()
{
	if (g_ms.env)
		ftarray__free_func(&g_ms.env, ms__func_free_env, NULL);
	if (g_ms.buffer)
		fts__free(&g_ms.buffer);
	if (g_ms.current_line)
		fts__free(&g_ms.current_line);
	if (g_ms.buffer_cd)
		fts__free(&g_ms.buffer_cd);
}