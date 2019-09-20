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

#include <minishell.prototypes.h>

char *ms__search_binary(char **env, char *binary_name)
{
	char *path;
	char *found;

	if (NULL != (path = ms__get_value(env, "PATH")))
	{
		found = ftsystm__find_in_path(path, ":", binary_name,
			ftstr__search_start);
		free(path);
		return (found);
	}
	return (NULL);
}

void print_promp()
{
	ft_printf("$> %s:\n", ftsystm__get_current_path());
}
