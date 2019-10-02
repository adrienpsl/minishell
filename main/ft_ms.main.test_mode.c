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

#include <minishell.h>

int main(int ac, char **av, char **env_system)
{
	t_env e = { 0, 0 };

	g_test = 1;
	if (NULL == (e.env = ft_strsplit_copy(env_system, 0)))
		return (EXIT_FAILURE);
	g_line = fts__init(20);
	ms__init(&e);
	free_env(&e);
	fts__free(&g_line);
	return (EXIT_SUCCESS);
	ac = (int)av;
}
