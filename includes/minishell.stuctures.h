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
#include <termios.h>

typedef struct s_ms
{
	int fd;
	int ctrl_c;
	t_array *env;
	t_array *env_tmp;
	t_s *buffer;
	t_s *current_line;
	t_s *buffer_cd;
	struct termios termios;
} t_ms;

typedef struct s_env_el
{
	char *key;
	char *value;
} t_env_el;

t_ms g_ms;
extern t_ms g_ms;

#endif
