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

#include <minishell.h>

/*
**	check if the char is in [a-zA-Z_] that compose all allowed char in 
**	shell variable.
*/

static int is_shell_variable_lexical(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
**	see the is_shell_variable_lexical to catch up
*/

static int not_shell_variable_lexical(char c)
{
	return (!(is_shell_variable_lexical(c)));
}

/*
**	put in end the end of the shell variable
**	if the end of that variable is the end of the string 
**	return the length of the string 
*/

static int get_end_of_variable(char *str)
{
	int end;

	end = ftstr_func_int(str,
		(void *)not_shell_variable_lexical,
		NULL);
	if (end == -1)
		end = ft_strlen(str);
	return (end);
}

/*
**	@env_variable:		a str of env split
**	@line_input:		the full input
**	compare the key ( env[n] ( key=variable ) ) of env_variable,
**	with the n char of the line_input composing the shell variable
*/

static int get_value_by_shell_variable(char *env_variable, void *line_input)
{
	int key_size;

	key_size = ft_strchr_int(env_variable, '=');
	if (key_size == -1)
		return (0);
	return (key_size == get_end_of_variable(line_input)
			&& OK == ft_strncmp(line_input, env_variable, key_size));
}

/*
**	if the **line is the start of a correct shell variable
**	find its value in env and add it (if founded) to the new_line
**	and move forward the *line of the length of the key. 
*/

int ms_replace_dollar(char **line, char **new_line, char **env)
{
	int length;
	char *value;

	if (line && line[0]
		&& line[0][0] == '$'
		&& is_shell_variable_lexical(line[0][1]))
	{
		*line += 1;
		value = ms__env_get_value(env, *line, get_value_by_shell_variable);
		length = get_end_of_variable(*line);
		ft_pstrjoin(*new_line, value ? value : "", 1, new_line);
		*line += length;
		return (1);
	}
	return (0);
}
