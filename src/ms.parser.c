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

#include "minishell.h"
#include "parser.h"

static void delimit_expansion(char *line, t_r *r)
{
	r->word = line + r->word_position;
	if (r->word[0] == '~')
		r->word_end = 1;
	else
		r->word_end =
		 ((r->word_end = ft_strchr(r->word, ' ')) == NOT_FIND) ?
		 ft_strlen(r->word) : r->word_end;
	r->word_separator = r->word[r->word_end];
	r->word[r->word_end] = '\0';
	r->word[r->word_end] = '\0';
}

static char *ms_replace_expansion(char *line, t_r *r)
{
	r->env_value = (ft_streq(r->word, "~")) ?
				   ms_get_value("HOME") :
				   ms_get_value(r->word + (r->word[0] == '$' ? 1 : 0));
	if (!r->env_value)
		r->env_value = "";
	r->word[0] = '\0';
	r->word[r->word_end] = r->word_separator;
	line = ft_strjoin(line, ft_strjoin(r->env_value, r->word + r->word_end, 0),
					  FREE_FIRST);
	return (line);
}

char **ms_parser()
{
	char *line;
	char **commands_split;
	t_r r;

	line = g_ms.is_test ?
		   ms_test_input_line() :
		   ms_get_line();
	while (line
		   && (r.word_position = ft_strchrstr(line, "$~")) > -1)
	{
		delimit_expansion(line, &r);
		line = ms_replace_expansion(line, &r);
	}
	commands_split = ft_strsplit(line ? line : "", ";");
	ft_str_free(&line);
	return (commands_split);
}
