
#include <libft.h>
#include <minishell.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "test.h"
//#include "../src/main.c"

// utils
void test_free(t_split *split);
void test_do_split(ms_test *test, t_split *split);
void new_passed_test();
void test_set_fd(char *str);
void test_ms_cd(ms_test test);

void test_ms_find_binary(ms_test test)
{
	t_split tSplit;
	char *binary_path;

	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	ms_init(tSplit.env);

	// binary path
	binary_path = ms_find_binary(test.binary_name);

	// say if I find it
	if (!ft_streq(test.binary_path, binary_path))
	{
		printf("ms env %d *******************************\n", test.nb_test);
		ft_test_if_streq(test.binary_path, binary_path, "binary find");
	}
}

void new_test_all()
{
	g_test = 1;
	new_passed_test();

	// if no path
	test_ms_find_binary((ms_test) {
	 .nb_test = 1,
	 .env = "",
	 .binary_name = "",
	 .binary_path = NULL
	});

	// if has binary
	test_ms_find_binary((ms_test) {
	 .nb_test = 2,
	 .env = "PATH=/bin",
	 .binary_name = "ls",
	 .binary_path = "/bin/ls"
	});

	test_ms_find_binary((ms_test) {
	 .nb_test = 3,
	 .env = "PATH=/bi:/Users/adpusel/code/42/minishell/prg",
	 .binary_name = "pgr_print_name",
	 .binary_path = "/Users/adpusel/code/42/minishell/prg/pgr_print_name"
	});

	// no binary
	test_ms_find_binary((ms_test) {
	 .nb_test = 2,
	 .env = "",
	 .binary_name = "PATH=/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/.nvm/versions/node/v10.15.3/bin:/Users/adpusel/code/mongodb/bin:/usr/local/bin:/usr/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools",
	 .binary_path = NULL
	});





	// no access

	// no access to the path var
}















