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

#ifndef MINISHELL_MINISHELL_PROTOTYPES_H
#define MINISHELL_MINISHELL_PROTOTYPES_H

/*
**	Env handling ---------------------------------------------------------------
*/
char **ms__convert_env(t_array *env, t_s *s);
char *ms__find_env_key(t_array *env, char *key);

/*
**	Utils ----------------------------------------------------------------------
*/
void ms__func_free_env(void *element, void*param);

#endif
