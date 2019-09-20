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

/*
**	Libft  ---------------------------------------------------------------------
*/
#include <ft_array.h>
#include <ft_s.h>

/*
**	Project  -------------------------------------------------------------------
*/
#include "minishell.structures.h"

/*
**	Prototypes  ================================================================
*/


/*
**	Utils
*/
char *ms__get_value(char **env, char *key);
void ms__env_add(char ***env, char *key, char *value);
void ms__env_delete(char **env, char *key);


#endif
