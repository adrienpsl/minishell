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

// utils qui me return le buffer avec le current path
char *get_current_path()
{
	static char buff[MAXPATHLEN + 1];

	ft_bzero(buff, MAXPATHLEN + 1);
	return (getcwd(buff, MAXPATHLEN));
}

int add_beguining_path(t_s *buffer);

// search at pathenv.
int go_path(t_array *env, t_s *buffer);
int cd__serialize_path(char **argv, t_array *env, t_s *buffer);

int ms__cd(char **argv, t_array *env, t_s *buffer)
{
	fts__clear(buffer);
	if (*argv && OK == ft_str_cmp("--", *argv))
		argv += 1;
	if (OK != cd__serialize_path(argv, env, buffer))
	    return (-1);

	return (0);
}