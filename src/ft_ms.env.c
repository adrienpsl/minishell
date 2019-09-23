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

static int option_i(char ***argv, char ***o_env)
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
	*o_env = new_env;
	return (OK);
}

static int option_u(char ***argv, char **env, char ***o_env)
{
	char **tmp_env;

	if (NULL == (tmp_env = ft_strsplit_copy(env, 0)))
		return (-1);
	while (OK == ft_strcmp("-u", **argv))
	{
		*argv += 1;
		if (NULL != **argv)
		{
			ms__env_delete(tmp_env, **argv);
			*argv += 1;
		}
		else
		{
			ft_strsplit_free(&tmp_env);
			print_usage(0);
			return (-1);
		}
	}
	*o_env = tmp_env;
	return (OK);
}

static int handle_option(char ***argv, char **env, char ***o_env)
{
	if (OK == ft_strcmp("-i", **argv))
		return option_i(argv, o_env);
	else if (OK == ft_strcmp("-u", **argv))
		return option_u(argv, env, o_env);
	else
	{
		print_usage((*argv)[0][1]);
		return (-1);
	}
}

/*
**	will parse the env stuff and return new env
*/
char **ms__env(char ***argv, char **env)
{
	char **new_env;

	new_env = NULL;
	if (**argv && ***argv == '-')
	{
		if (OK != handle_option(argv, env, &new_env))
			return (NULL);
	}
	if (NULL == **argv)
	{
		ft_strsplit_print(new_env ? new_env : env, '\n');
		ft_printf("\n");
		ft_strsplit_free(&new_env);
		return (NULL);
	}
	return (new_env);
}