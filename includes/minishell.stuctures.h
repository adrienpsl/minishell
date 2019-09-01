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

#include <ft_array.h>
#include <ft_s.h>

typedef struct s_ms
{
	t_array *env_current;
	t_array *env_tmp;
	t_s *buffer;
} t_ms;

typedef struct s_env_el
{
	char *key;
	char *value;
} t_env_el;

t_ms g_ms;
extern t_ms g_ms;

#endif