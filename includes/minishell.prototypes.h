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
# include <ft_array.h>
# include <ft_s.h>
# include <libft_define.h>
# include <ft_printf.h>
# include <ft_systm.h>
# include <stdlib.h>



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
char *ms__search_binary(char **env, char *binary_name);
char *ms__get_line(char **env);

/*
**	Intern function
*/
int cd__change_directory(char *path, char *argv, int print);
void print_promp();
void clean_char(t_s *line);
void ms_signal_exec(int sign);
void ms_signal_minishell(int sign);


#endif
