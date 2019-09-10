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

#include <minishell.stuctures.h>
#include <minishell.prototypes.h>
# include "libft.h"

static int print_usage()
{
	ft_printf("usage: env [-i] [name=value ...] [-u name]\n"
			  "          [utility [argument ...]]");
	return (-1);
}

int deep_copy_link(void *p_dest, void *p_src, void *null)
{
	t_env_el *dest;
	t_env_el *src;
	(void)null;

	dest = p_dest;
	src = p_src;
	if (
		NULL == (dest->key = ft_strdup(src->key))
		|| NULL == (dest->value = ft_strdup(src->value))
		)
		return (1);
	return (0);
}

int option_u(char ***argv, t_array *env, t_array **env_tmp)
{
	if (NULL != (*env_tmp = ftarray__copy_func(env, deep_copy_link, NULL)))
	{
		while (OK == ft_str_cmp("-u", **argv))
		{
			(*argv) += 1;
			if (NULL != **argv)
			{
				ms__env_remove(*env_tmp, **argv);
				(*argv) += 1;
			}
			else
				return (-1);
		}
		return (0);
	}
	return (-1);
}

static int option_i(char ***argv, t_array **env_tmp)
{
	if (NULL != (*env_tmp = ftarray__init(10, sizeof(t_env_el))))
	{
		while (
			NULL != **argv
			&& ft_strchr(**argv, '=') > 0
			)
		{
			ms__env_add(*env_tmp, NULL, NULL, **argv);
			(*argv) += 1;
		}
	}
	return (0);
}

static int handle_options(char ***argv, t_array *env, t_array **env_tmp)
{
	if (OK == ft_str_cmp("-u", **argv))
	{
		if (OK == option_u(argv, env, env_tmp))
			return (OK);
		else
			return (print_usage());
	}
	else if (OK == ft_str_cmp("-i", **argv))
	{
		return (option_i(argv, env_tmp));
	}
	else
		return (print_usage());
}

/**
 * @brief
 * @param argv
 * @param env
 * @return success == remain argument,
 */
char **ms__env(char **argv, t_ms *ms)
{
	if (
		*argv
		&& **argv == '-'
		)
	{
		if (OK != handle_options(&argv, ms->env, &ms->env_tmp))
			return (NULL);
	}
	if (NULL == *argv)
	{
		ftarray__func(get__env(ms), ms__print_env, NULL);
		return (NULL);
	}
	return (argv);
}
