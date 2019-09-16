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
#include <minishell.prototypes.h>
#include "libft.h"
#include "ft_ms.cd.h"

int static add_start_if_relative(t_s *buffer)
{
	char *current_dir_path;

	if ('/' != buffer->data[0])
	{
		if (NULL != (current_dir_path = get_current_path()))
		{
			fts__add_at(buffer, "/", 0);
			fts__add_at(buffer, current_dir_path, 0);
			return (OK);
		}
		else
			return (-1);
	}
	return (OK);
}

int static test_and_go_dir(char *path, char *argv)
{
	if (OK != access(path, F_OK))
	{
		ft_printf("cd: no such file or directory: %s\n", argv);
		return (-1);
	}
	if (OK != access(path, R_OK))
	{
		ft_printf("cd: permission denied: %s\n", argv);
		return (-1);
	}
	if (OK != chdir(path))
	{
		ft_printf("cd : not a directory: %s\n", argv);
		return (-1);
	}
	return (OK);
}

int cd_move_directory(t_s *buffer, t_array *env)
{
	int ret;
	char *argument;
	char *old_path;

	ret = -1;
	if (NULL == (argument = ft_strdup(buffer->data))
		|| NULL == (old_path = ft_strdup(get_current_path())))
		return (ret);
	if (OK == add_start_if_relative(buffer))
	{
		if (OK == test_and_go_dir(buffer->data, argument))
		{
			ms__env_add(env, "OLDPATH", old_path, NULL);
			ret = OK;
		}
	}
	free(argument);
	free(old_path);
	return (ret);
}