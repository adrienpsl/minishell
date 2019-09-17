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

typedef struct func_name
{
	char *name;
	int (*f)(char **argv, t_array *env);
} t_n;

int exec_builtin(char **argv, t_array *env)
{
	int i;
	static t_n g_func_arr[10] = {
		{ "unsetenv", ms__unsetenv },
		{ "setenv",   ms__setenv },
		{ "exit",     ms__exit },
		{ "cd",       ms__cd },
		{ "echo",     ms__echo },
	};

	i = 0;
	while (i < 5)
	{
		if (OK == ft_str_cmp(g_func_arr[i].name, argv[0]))
			return (g_func_arr[i].f(argv + 1, env));
		i++;
	}
	return (ms__exec(argv, env));
}

void loop_on_command(char **argv, t_array *env)
{
	t_array *env_tmp;

	if (argv == NULL || 0 < argv[0])
		return;
	if (ft_str_cmp("env", argv[0]))
	{
		if (NULL != (env_tmp = ms__env(&argv, env)))
			loop_on_command(argv + 1, env_tmp);
		exec_builtin(argv, env_tmp == NULL ? env : env_tmp);
		if (env_tmp)
			ftarray__free_func(&env_tmp, ms__func_free_env, NULL);
	}
}
