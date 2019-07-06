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

static int matched_env_variable(char *env_key_value, char *searched)
{
	ssize_t i;

	i = ft_str_char(env_key_value, '=');
	if (i > 0)
		return (!ft_mem_cmp(env_key_value, searched, i));
	return (0);
}

static int delete_variable(char ***p_env, int i)
{
	char **env;

	env = *p_env;
	free(*(env + i));
	while (*(env + i) != NULL)
	{
		*(env + i) = *(env + i + 1);
		i++;
	}
	return (0);
}

int ft_ms_env_remove(char *removing_var, t_ms *ms)
{
	int i;
	char **env;

	if (!removing_var)
		return (BAD_DELETING_KEY);
	env = ms->p_env;
	i = -1;
	while (*(env + ++i) != NULL)
	{
		if (matched_env_variable(*(env + i), removing_var))
			return delete_variable(&env, i);
	}
	return (BAD_DELETING_KEY);
}
