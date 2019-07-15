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

static char *one_argument(char *argv)
{
	if (ft_strchr(argv, '$') != -1)
		return (ft_putstr_retptr("No $ en env variable", NULL));
	if (ft_strnchr(argv, '=') != 1)
		return (ft_putstr_retptr("The env separator is one single =", NULL));
	else
		return ft_strdup(argv);
}

static char *two_arguments(char **argv)
{
	if (ft_strchr(argv[0], '$') != -1 || ft_strchr(argv[1], '$') != -1)
		return (ft_putstr_retptr("No $ en env variable", NULL));
	if (ft_strchr(argv[0], '=') != -1 || ft_strchr(argv[1], '=') != -1)
		return ft_putstr_retptr("If two elements are supply no =", NULL);
	else
		return (ft_strjoinby(argv[0], "=", argv[1], 0));
}

int ft_setenv(char **argv)
{
	int i;
	char *tmp_str;

	i = ft_str_split_count(argv);
	if (i == 1)
		tmp_str = one_argument(*argv);
	else if (i == 2
			 && ft_strchr(*argv, '$' == -1)
			 && ft_strchr(argv[1], '$' == -1))
		tmp_str = two_arguments(argv);
	else
		return (ft_putstr_retint("Bad number argument given to set env", -1));
	return (tmp_str
			&& (m.env = ft_str_split_add(m.env, tmp_str, 1)) ?
			(0) : (-1));
}

int ft_unsetenv(char *removing_var)
{
	int i;

	i = ft_strsplit_search(m.env, ms_search_function, removing_var);
	if (i > -1)
	{
		free(m.env[i]);
		while (m.env[i] != NULL)
		{
			m.env[i] = m.env[i + 1];
			i++;
		}
		return (0);
	}
	return (-1);
}

void ft_env()
{
	ft_strsplit_print(m.env, '\n');
}