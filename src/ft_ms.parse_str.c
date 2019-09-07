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

#include "libft.h"

/*
 * I build the split
 * I create an array of that split
 * I copy the 2 element
 * I clear the split mem
 * */
t_array *ms__parse_str(char *input, char *sep)
{
	int size;
	char **split;
	t_array *a_parsed;

	if (
		NULL == (split = ft_strsplit(input, sep))
		)
		return (NULL);
	size = ft_strsplit_count(split);
	if (
		NULL == (a_parsed = ftarray__init_data(split, size, sizeof(char **)))
		)
		return (NULL);
	free(split);
	return (a_parsed);
}