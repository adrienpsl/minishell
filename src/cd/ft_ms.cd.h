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

#ifndef FT_MS_CD
#define FT_MS_CD

/*
**	Libft  ---------------------------------------------------------------------
*/
# include <ft_s.h>
# include <ft_array.h>
# include <libft_define.h>
# include <ft_str.h>
# include <ft_printf.h>
# include <minishell.prototypes.h>

# include <ft_systm.h>

/*
**	Prototypes  ----------------------------------------------------------------
*/
int cd__serialize_path(char **argv, t_array *env, t_s *buffer, int *print_path);
int cd_move_directory(t_s *buffer, t_array *env);

#endif
