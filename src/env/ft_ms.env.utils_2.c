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

#include <ft_array.h>
#include <ft_str.h>
#include <minishell.stuctures.h>
#include <ft_s.h>
#include <ft_mem.h>
#include <ft_printf.h>

int find_variable(void *v_element, void *param)
{
	t_env_el *element;
	char *key;

	element = v_element;
	key = param;
	if (0 == ft_str_cmp(element->key, key))
		return (1);
	else
		return (0);
}


char *ms__find_env_key(t_array *env, char *key)
{
	t_env_el *element;
	static char *fail = "";

	element = ftarray__func(env, find_variable, key);
	if (element)
		return (element->value);
	else
		return (fail);
}

static void build_variable(t_env_el *element, t_s *s)
{
	fts__clear(s);
	fts__add(s, element->key);
	fts__add(s, "=");
	fts__add(s, element->value);
}

char **ms__convert_env(t_array *env, t_s *s)
{
	char **env_system;
	t_env_el *element;

	if (NULL == (env_system =
					 ft_memalloc(sizeof(char **) * (env->length + 1))))
		return (NULL);
	ftarray__set_start(env);
	while ((element = ftarray__next(env)))
	{
		build_variable(element, s);
		if (NULL == (*env_system = ft_strdup(s->data)))
			return (NULL);
		env_system++;
	}
	return (env_system - env->length);
}
