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
#include "libft.h"
#include "ft_ms.cd.h"

int ms__cd(char **argv, t_array *env, t_s *buffer)
{
	int print_new_path;

	fts__clear(buffer);
	if (*argv && OK == ft_str_cmp("--", *argv))
		argv += 1;
	if (OK != cd__serialize_path(argv, env, buffer, &print_new_path))
		return (-1);
	if (OK != cd_move_directory(buffer, env))
		return (-1);
	if (print_new_path)
		ft_printf("%s\n", get_current_path());
	return (OK);
}