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
#include <ft_systm.h>

struct termios g_termios;
t_s *g_line;
int g_ctrl;

void ms__activate_raw_mode(struct termios *saved_termios)
{
	struct termios termios;
	//// TODO :  check the return system

	tcgetattr(STDIN_FILENO, &termios);
	tcgetattr(STDIN_FILENO, saved_termios);
	termios.c_lflag &= ~(ICANON | ECHO);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

char *search_binary(char **env, char *binary_name)
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

void delete_char(t_s *line)
{
	ft_putstr_fd("\b \b", 1);
	if (line->length)
		fts__remove_from(line, line->length - 1);
}

void clean_char(t_s *line)
{
	while (line->length)
		delete_char(line);
}

void tab_char(t_s *line, char **env)
{
	char *found;

	if (NULL != (found = search_binary(env, line->data)))
	{
		clean_char(line);
		if (OK == fts__add(line, found))
			ft_printf(line->data);
		free(found);
	}
}

void handle_input(char buffer[4], t_s *line, char **env)
{
	if (OK == ft_strcmp(MS__DEL, buffer))
		delete_char(line);
	else if (OK == ft_strcmp(MS__TAB, buffer))
		tab_char(line, env);
	else if ('\0' == buffer[1])
	{
		ft_printf(buffer);
		fts__add(line, buffer);
	}
}

char *ms__get_line(char **env)
{
	char buffer[5] = { 0 };

	while (OK != ft_strcmp(buffer, "\n"))
	{
		ft_bzero(&buffer, 5);
		if (read(0, buffer, 4) <= 0)
			break;
		if (OK != ft_strcmp(buffer, "\n"))
			handle_input(buffer, g_line, env);
	}
	return (NULL);
}

void print_promp()
{
	ft_printf("$> %s:\n", ftsystm__get_current_path());
}

void ms_signal_minishell(int sign)
{
	(void) sign;
	g_ctrl = 1;
	clean_char(g_line);
	print_promp();
}


int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	g_ctrl = 0;

	signal(SIGINT, ms_signal_minishell);
	g_line = fts__init(10);
	ms__activate_raw_mode(&g_termios);
	print_promp();
	char **env = ft_strsplit(
		"PATH=/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/.nvm/versions/node/v10.15.3/bin:/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/code/mongodb/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools",
		" ");
	ms__get_line(env);

	printf("\n%s \n", g_line->data);

	fts__free(&g_line);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_termios);
	return (EXIT_SUCCESS);
}