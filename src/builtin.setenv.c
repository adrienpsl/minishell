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

char **ms_set_env(char **argv, char **env)
{
	int i;
	char *tmp_str;

	i = ft_str_split_count(argv);
	if (i == 1)
		tmp_str = one_argument(*argv);
	else if (i == 2)
		tmp_str = two_arguments(argv);
	else
		return (ft_putstr_retptr("Bad number argument given to set env", NULL));
	return (tmp_str ? ft_str_split_add(env, tmp_str, FREE) : NULL);
}

int ft_setenv(char **argv)
{
	char **new_argv;

	if (!argv)
		return (-1);
	if ((new_argv = ms_set_env(argv, m.env)))
	{
		m.env = new_argv;
		return (0);
	}
	else
		return (-1);
}

