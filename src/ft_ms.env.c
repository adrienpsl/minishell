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

#include <libft.h>
#include <minishell.prototypes.h>

static int print_usage(char bad_option)
{
	if (bad_option)
		ft_printf("env: illegal option -- %c\n", bad_option);
	else
		ft_printf("env: option requires an argument -- u\n");
	ft_printf("usage: env [-i] [name=value ...] [-u name]\n"
			  "          [utility [argument ...]]\n");
	return (-1);
}


static int option_i(char ***argv, t_env *e)
{
	char **new_env;

	(*argv) += 1;
	if (NULL == (new_env = ft_strsplit("", " ")))
		return (-1);
	while (NULL != **argv && 0 < ft_strchr_int(**argv, '='))
	{
		ms__env_add(&new_env, NULL, NULL, **argv);
		*argv += 1;
	}
	update_env_tmp(new_env, e);
	return (OK);
}

// elle prend le env, et en fonction va update le new env
static int option_u(char ***argv, t_env *e)
{
	char **new_env;

	if (NULL == (new_env = ft_strsplit_copy(*get_env(e), 0)))
		return (-1);
	while (OK == ft_strcmp("-u", **argv))
	{
		*argv += 1;
		if (NULL != **argv)
		{
			ms__env_delete(new_env, **argv);
			*argv += 1;
		}
		else
		{
			ft_strsplit_free(&new_env);
			print_usage(0);
			return (-1);
		}
	}
	update_env_tmp(new_env, e);
	return (OK);
}
/*
**	will parse the env stuff and return new env
*/
int ms__env(char ***argv, t_env *e)
{
	int ret;

	ret = OK;
	if (**argv && ***argv == '-')
	{
		if (OK == ft_strcmp("-i", **argv))
			ret = option_i(argv, e);
		else if (OK == ft_strcmp("-u", **argv))
			ret = option_u(argv, e);
		else
		{
			print_usage((*argv)[0][1]);
			return (-1);
		}
	}
	if (OK == ret && NULL == **argv)
	{
		ft_strsplit_print(*get_env(e), '\n');
		ft_printf("\n");
		return (1);
	}
	return (ret);
}