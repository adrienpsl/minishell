
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

void test_ms_handle_binary(ms_test test)
{
	t_split tSplit;
	int ret;

	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	ms_init(tSplit.env);

	ret = ms_handle_binary(tSplit.argv);

	if (
	 !ft_streq(test.print, g_test_buffer) ||
	 ret != test.ret_int
	 )
	{
		printf("ms_handle_binary %d ******************* \n", test.nb_test);

		ft_test_if_streq(test.print, g_test_buffer, NULL);
		if (ret != test.ret_int)
			printf("ret diff %d // %d \n", test.ret_int, ret);
	}

	// free
	ms_free(g_ms.env);
	test_free(&tSplit);
}

void new_test_all()
{
	g_test = 1;
	new_passed_test();


	// if no argv
	test_ms_handle_binary((ms_test) {
	 .nb_test = 58,
	 .env = "",
	 .argv = "",
	 .print = "",
	 .ret_int = -1
	});

	// if no path
	test_ms_handle_binary((ms_test) {
	 .nb_test = 59,
	 .env = "",
	 .argv = "ls",
	 .print = "The env variable : PATH is no set.\n"
			  "mimishell: command not found: ls\n",
	 .binary_path = NULL,
	 .ret_int = -1
	});

	// if has binary
	test_ms_handle_binary((ms_test) {
	 .nb_test = 60,
	 .env = "PATH=/bin:/Users/adpusel/code/42/minishell/prg",
	 .argv = "ls",
	 .print = "",
	 .ret_int = 0
	});

	// has binary and arguments
	test_ms_handle_binary((ms_test) {
	 .nb_test = 61,
	 .env = "PATH=/bin:/Users/adpusel/code/42/minishell/prg",
	 .binary_name = "ls",
	 .argv = "ls a b",
	 .print = "",
	 .ret_int = 0
	});

	// path and no binary
	test_ms_handle_binary((ms_test) {
	 .nb_test = 62,
	 .env = "PATH=/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/.nvm/versions/node/v10.15.3/bin:/Users/adpusel/code/mongodb/bin:/usr/local/bin:/usr/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools",
	 .argv = "ls /",
	 .print = "mimishell: command not found: ls\n",
	 .ret_int = -1
	});

}















