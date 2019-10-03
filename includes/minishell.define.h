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

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# include <libft.h>
# include <minishell.structures.h>
# define MS__NAME "minishell: "
# define MS__EXIT 4242
# define MS__DEL "\177"
# define MS__TAB "\t"

/*
**	this will be the buffer of the current user input, in raw mode.
*/
t_s *g_line;
extern t_s *g_line;

/*
**	allow binary to disable the raw mode.
*/
int g_ms_test;
extern int g_ms_test;

#endif
