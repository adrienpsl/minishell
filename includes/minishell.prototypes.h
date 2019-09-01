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

#ifndef MINISHELL_MINISHELL_PROTOTYPES
#define MINISHELL_MINISHELL_PROTOTYPES

#include <ft_array.h>
#include <ft_s.h>

/*
**	Env handling ---------------------------------------------------------------
*/
char **ms__convert_env(t_array *env, t_s *s);
char *ms__find_env_key(t_array *env, char *key);
int find_variable(void *v_element, void *param);

/*
**	Utils ----------------------------------------------------------------------
*/
void ms__func_free_env(void *element, void*param);

#endif
