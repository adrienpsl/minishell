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

static int count_env_variable(char **env)
{
	int i;

	i = 0;
	while (*(env + i) != NULL)
		i++;
	return (i);
}

int ft_ms_env_copy(char **env, t_ms *ms)
{
	char **tmp_env;
	char *tmp_var;
	int i;

	if (!env)
		return (NO_ENV);
	i = count_env_variable(env);
	if (ft_mem((void **) &tmp_env, sizeof(char **) * (i + 2)))
		return (MEMORY_LACK);
	i = 0;
	while (*(env + i) != NULL)
	{
		if (ft_mem_dup((void **) &tmp_var, *(env + i), STRING_MODE))
			return (MEMORY_LACK);
		*(tmp_env + i) = tmp_var;
		i++;
	}
	ms->p_env = tmp_env;
	return (0);
}

// protection if not = in the add stuff
int ft_ms_env_add(char *new_var, t_ms *ms)
{
	int i;
	char *tmp_str;
	char **env;

	if (!new_var
		|| ft_str_char(new_var, '=') == -1
		|| ft_str_char_count(new_var, '=') != 1)
		return (BAD_VAR);
	env = ms->p_env;
	i = count_env_variable(env);
	if (ft_mem_dup((void **) &tmp_str, new_var, STRING_MODE))
		return (-1);
	*(env + i) = tmp_str;
	if (ft_ms_env_copy(env, ms))
		return (NO_ENV);
	return (0);
}