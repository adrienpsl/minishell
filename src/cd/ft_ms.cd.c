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
#include <minishell.defines.h>
#include <sys/param.h>
#include "libft.h"

char *get_current_path()
{
	static char buff[MAXPATHLEN + 1];

	return (getcwd(buff, MAXPATHLEN));
}
int go_path(t_array *env, t_s *buffer);
int cd__serialize_path(char **argv, t_array *env, t_s *buffer);

int add_start_if_relative(t_s *buffer)
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

int ms__cd(char **argv, t_array *env, t_s *buffer)
{
	fts__clear(buffer);
	if (*argv && OK == ft_str_cmp("--", *argv))
		argv += 1;
	if (OK != cd__serialize_path(argv, env, buffer))
		return (-1);
	if (OK != add_start_if_relative(buffer))
	    return (-1);
	// go in file, update if needed env variable,
	// print if need the last path
	return (0);
}