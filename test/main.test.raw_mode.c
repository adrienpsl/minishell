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

#include <libft.h>
#include <sys/termios.h>
#include <minishell.defines.h>
#include <ft_s.h>
#include <minishell.prototypes.h>

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	signal(SIGINT, ms_signal_minishell);
	g_line = fts__init(10);
//	ms__activate_raw_mode(&g_termios);
	print_promp();
	char **env = ft_strsplit(
		"PATH=/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/.nvm/versions/node/v10.15.3/bin:/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/code/mongodb/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools",
		" ");
	ms__get_line(env, NULL, NULL);

	printf("\n%s \n", g_line->data);

	fts__free(&g_line);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_termios);
	return (EXIT_SUCCESS);
}