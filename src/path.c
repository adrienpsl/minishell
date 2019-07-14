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

#include <dirent.h>
#include "minishell.h"

// je donne un path a cette fonction, et elle va loop dessus et me resortir le resultat ?

char *display_dir_content(char *path, char *searched_str)
{
	DIR *dir;
	struct dirent *dp;

	dir = opendir(path);
	if (dir)
		while ((dp = readdir(dir)))
		{
			if (ft_str_search(dp->d_name, searched_str) > -1)
				ft_printf("%s  ", dp->d_name);
			if (*searched_str == 0)
				ft_printf("%s  ", dp->d_name);
		}
	return (NULL);
}

// pour le path, je split ma variable path

// je boucle sur elle et pour chacun des file donnee,
// je fais une boucle et je cherche mes
// j'open mon dir et je loop sur tt les elements que j'ai dedans
// une fonction qui va
