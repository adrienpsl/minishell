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
#include "libft.h"

void test_get_env_variable(char *line, char **env, int end, char *res, int test)
{
	m.env = env;
	line = get_env_variable(line, end);
	if (!ft_streq(line, res))
	{
		printf("Error get_env_variable : %d \n", test);
		printf("res : %s \n", res);
		printf("ret : %s \n", line);
	}
}
