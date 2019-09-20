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

int option_i(t_env_ret *ret)
{
	int position;

	ret->argv += 1;
	if (NULL == (ret->env = ft_strsplit("", " ")))
		return (-1);
	while (NULL != ret->argv
		   && 0 < (position = ft_strchr(*ret->argv, '=')))
	{
		(*ret->argv)[position] = '\0';
		ms__env_add(&ret->env, *ret->argv, (*ret->argv) + position + 1);
		ret->argv += 1;
	}
	return (OK);
}

int option_u(t_env_ret *ret, char **env)
{
	if (NULL == (ret->env = ft_strsplit_copy(env, 0)))
		return (-1);
	while (OK == ft_strcmp("-u", *ret->argv))
	{
		ret->argv += 1;
		if (NULL != *ret->argv)
		{
			ms__env_delete(ret->env, *ret->argv);
			ret->argv += 1;
		}
		else
		{
			ft_strsplit_free(&ret->env);
			return (print_usage(0));
		}
	}
	return (OK);
}

t_env_ret *ms_env(char **argv, char **env)
{
	static t_env_ret ret;

	ret.argv = argv;
	ft_bzero(&ret, sizeof(t_env_ret));
	if (*ret.argv && **ret.argv == '-')
	{
		if (OK == ft_strcmp("-i", *argv))
		{
			if (OK != option_i(&ret))
				return (NULL);
		}
		if (OK == ft_strcmp("-u", *argv))
		{
			if (OK != option_u(&ret, env))
				return (NULL);
		}
	}
	if (NULL == *ret.argv)
	{
		ft_strsplit_print(ret.env ? ret.env : env, '\n');
		ft_strsplit_free(&ret.env);
		return (NULL);
	}
	return (&ret);
}