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

#ifndef MINISHELL_STRUCTURES
#define MINISHELL_STRUCTURES

typedef struct s_env_ret
{
	char **argv;
	char **env;
} t_env_ret;

typedef int (*t_func)(char **arg, char ***env);

typedef struct s_element_func
{
	char *name;
	t_func func;
} t_element_func;

#include <ft_array.h>
#include <ft_s.h>
#include <termios.h>

#endif
