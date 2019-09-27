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

#ifndef MINISHELL_MINISHELL_DEFINES
#define MINISHELL_MINISHELL_DEFINES

#include <ft_s.h>
#include <minishell.structures.h>
#include <termios.h>

# define MS__NAME "minishell: "
# define MS__EXIT 4242
# define MS__DEL "\177"
# define MS__TAB "\t"

struct termios g_termios;
t_s *g_line;

#endif
