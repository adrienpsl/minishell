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

#include <minishell.prototypes.h>
#include "libft.h"

void loop_on_command(char **argv, t_array *env)
{
	t_array *env_tmp;

	if (argv == NULL || 0 < argv[0])
		return;
	if (ft_str_cmp("env", argv[0]))
	{
		if (NULL == (argv = ms__env(argv, env, &env_tmp)))
			loop_on_command(argv, env_tmp);
		// do the stuff or th
		// je copy env
		// je le passe aver la line a mon element

		// clean env

		if (env_tmp)
			ftarray__free_func(&env_tmp, ms__func_free_env, NULL);
	}
}
