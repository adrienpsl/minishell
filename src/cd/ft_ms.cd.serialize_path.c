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

#include <ft_s.h>
#include <minishell.defines.h>
#include <minishell.prototypes.h>
#include "libft.h"
#include "ft_ms.cd.h"

int static add_env_var(t_array *env, t_s *buffer, int size)
{
	char *key;
	char *value;

	if (size == 0)
		key = "HOME";
	else
		key = "OLDPATH";
	value = ms__find_env_key(env, key);
	if ('\0' != *value)
	{
		fts__add(buffer, value);
		return (OK);
	}
	else
	{
		ft_printf(MS__NAME"line %d: cd: %s not set\n", __LINE__, key);
		return (-1);
	}
}

int static  replace_in_path(char **argv, t_s *buffer)
{
	char *current_path;

	current_path = get_current_path();
	if (NULL == current_path)
		return (-1);
	fts__add(buffer, current_path);
	if (OK == fts__replace_str(buffer, argv[0], argv[1]))
		return (OK);
	else
	{
		ft_printf("cd: string not in pwd: %s\n", argv[0]);
		return (-1);
	}
}

int cd__serialize_path(char **argv, t_array *env, t_s *buffer, int *print_path)
{
	int size;
	int ret;

	size = ft_strsplit_count(argv);
	if (0 == size
		|| (1 == size && OK == ft_str_cmp("-", argv[0])))
	{
		*print_path = 1;
		ret = add_env_var(env, buffer, size);
	}
	else if (1 == size)
	{
		*print_path = 0;
		fts__add(buffer, *argv);
		ret = OK;
	}
	else if (2 == size)
	{
		*print_path = 1;
		ret = replace_in_path(argv, buffer);
	}
	else
		ret = -1;
	return (ret);
}
