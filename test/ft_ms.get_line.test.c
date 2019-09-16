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
#include <fcntl.h>
#include <sys/stat.h>
#include <ft_test.h>
#include <termios.h>
#include "libft.h"


// je veux ecrire dans un fichier les data et ce fichier dois
//

int test_set_fd(char *data)
{
	int fd;
	mkdir("test_dir", 0777);
	fclose(fopen("test_dir/current_test", "w"));
	fd = open("test_dir/current_test", O_CREAT | O_RDWR);
	write(fd, data, ft_strlen(data));
	close(fd);
	return open("test_dir/current_test", O_RDONLY);
}

typedef struct ms_test
{
	int nb_test;
	int nb_line;
	char *line_data;
	char *res_return;
	char *res_buff;
	int read_size;
} mt_test;

static void
test_function(mt_test test)
{
	char **env = ft_strsplit(
		"PATH=/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/.nvm/versions/node/v10.15.3/bin:/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/code/mongodb/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools",
		" ");
	ms__init(env);

	g_ms.fd = test_set_fd(test.line_data);
	char *ret = ms__get_line(test.read_size);

	if (
		test_cmp_str(test.res_return, ret)
		)
		log_test_line(test.nb_test, test.nb_line)
	if (
		test_cmp_buff(test.res_buff)
		)
		log_test_line(test.nb_test, test.nb_line)

	close(g_ms.fd);
	ft_strsplit_free(&env);
	ms__free();
}

void test_ms__get_line()
{
	g_test = 1;
	test_clear_testbuff();

	/*
	* test simple string
	* */
	{
		// test nothing
		test_function((mt_test)
						  { 0, L, "\n", "", "\n", 1 }
		);

		//				 test one char
		test_function((mt_test){ 0, L, "a\n", "a", "a\n", 1 });

		//				 test multiple char
		test_function((mt_test){ 0, L, "minh est vraiment tres jolie\n",
								 "minh est vraiment tres jolie",
								 "minh est vraiment tres jolie\n", 1 });
	}

	/*
	* test tab
	* */
	{
		// test search
		test_function((mt_test){ 0, L, "tes\t\n", "test", "test\n", 1 });

		// test search not exist
		test_function((mt_test){ 0, L, "toto\t\n", "toto", "toto\n", 1 });

		// test search begin exist
		test_function(
			(mt_test){ 0, L, "test toto\t\n", "test toto", "test toto\n", 1 });
	}

	g_test = 0;
	//	struct termios termios;
	//	ms__activate_raw_mode(&termios);

	//	test_function(
	//		(mt_test){ 0, L, "t\0e\0stl\177\n", "test", "testl\b \b\n", 2 });

	//	tcsetattr(STDIN_FILENO, TCSANOW, &termios);

	// TODO : pas pu tested del, I need to activate the row mode to do that
	//	//	/*
	//	//	* test del
	//	//	* */
	//		{
	//			// test search
	//			test_function((mt_test){ 0, L, "testl\177\n", "test", "testl\b \b\n", 1 });
	//		}
	//


}