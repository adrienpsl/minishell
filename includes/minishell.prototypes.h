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
//int ms__handle_binary(char **argv, char ***env);
int ms__unsetenv(char **argv, char ***env);
int ms__setenv(char **argv, char ***env);
int ms__cd(char **argv, char ***env);
int ms__env(t_data *d, t_env *e);
void ms__env_add(char ***env, char *key, char *value, char *variable);
int ms__command(char *line, t_env *e);

/*
**	Getter / setter ------------------------------------------------------------
*/
void update_env_tmp(char **new, t_env *e);
char ***get_env(t_env *e);
void free_env(t_env *e);
int ms__dispatch(t_data *d, t_env *e);

/*
**	Utils
*/
int find_variable(char *current, void *searched);
char *ms__env_get_value(char **env, char *key,int (*func)(char*, void*));
void ms__env_add(char ***env, char *key, char *value, char *variable);
void replace_dollar(char **line, char **new_line, char **env);
void ms__env_delete(char **env, char *key);
char * ms__search_binary(
	char **env,
	char *binary_name,
	int (*f)(char *, char *));
int ms__get_line(
	const char *const *const env,
	t_s *const line, char **output);
int replace_dollar_tilde(
	const char **env,
	const char **line);
int ms__init(t_env *e, int test);
int ms__echo(char **argv, char ***env);

/*
**	Intern function
*/
int cd__change_directory(char *path, int print);
void print_prompt();
void clean_char(t_s *line);
void ms_signal_exec(int sign);
void ms_signal_minishell(int sign);
int get_line_test(
	t_s *const line,
	char **output);

#endif
