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

#ifndef MINISHELL_PROTOTYPES_H
# define MINISHELL_PROTOTYPES_H

/*
**	My Includes  ---------------------------------------------------------------
*/
# include <libft.h>
# include "minishell.structures.h"

/*
**	Systems Includes  ----------------------------------------------------------
*/
# include <termios.h>

/*
**	Prototypes  ================================================================
*/
int		ms__unsetenv(char **argv, char ***env);
int		ms__setenv(char **argv, char ***env);
int		ms__cd(char **argv, char ***env);
int		ms__env(char ***argv, t_env *e);
int		ms__dispatch(char **argv, t_env *e);
int		ms_replace_dollar(char **line, char **new_line, char **env);
int		find_variable(char *current, void *searched);
int		replace_dollar_tilde(char **env, char *line, char **output);
int		ms__init(char ***env);
int		ms__echo(char **argv, char ***env);
int		cd__change_directory(char *path, int print);
char	*ms__env_get_value(char **env, char *key, int (*func)(char*, void*));
char	***get_env(t_env *e);
void	ms__env_add(char ***env, char *key, char *value, char *variable);
void	update_env_tmp(char **new, t_env *e);
void	ms__env_add(char ***env, char *key, char *value, char *variable);
void	ms__env_delete(char **env, char *key);
void	print_prompt();
void	clean_char(t_s *line);
void	ms_signal_exec(int sign);
void	ms_signal_minishell(int sign);
int		get_line_test(
	t_s *const line,
	char **output);
char	*ms__search_binary(
	char **env,
	char *binary_name,
	int (*f)(char *, char *));
int		ms__get_line(
	char **env,
	t_s *const line, char **output);

#endif
