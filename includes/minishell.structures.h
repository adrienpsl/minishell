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

#ifndef MINISHELL_STRUCTURES_H
# define MINISHELL_STRUCTURES_H

/*
**	the builtin type function, like cd or setenv.
*/
typedef int		(*t_func)(char **arg, char ***env);

/*
**	allow when an env command is trigger, to create an use an tmp env
*/
typedef struct	s_env
{
	char		***env;
	char		**tmp_env;
}				t_env;

#endif
