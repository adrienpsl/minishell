
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
//void write_in_file(char *str);

// write in my file and open fd
void open_fd_with_data(char *data, char *location)
{
	int fd;
	// go to that file
	chdir(location);
	// create the directory
	mkdir("test_files", 0777);
	// if there is a file, clean it
	fclose(fopen("test_files/current_test", "w"));
	// write in it
	fd = open("test_files/current_test", O_CREAT | O_RDWR);
	write(fd, data, strlen(data));
	// set stream on that file
	g_mst.fd = open("test_files/current_test", O_RDONLY);
}


void test_ms_cd(ms_test test)
{
	// init
	t_split tSplit;
	int ret;

	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	ms_init(tSplit.env);

	// function tested
	g_ms.argv = tSplit.argv;
	g_ms.argv_size = ft_strsplit_count(g_ms.argv);
	ret = ms_env();

	// print error
	if (
	 ft_strsplit_cmp(tSplit.env_tmp, g_ms.env_tmp) ||
	 ft_strsplit_cmp(tSplit.argv_end, g_ms.argv) ||
	 !ft_streq(test.print, g_test_buffer) ||
	 ret != test.ret_int
	 )
	{
		printf("ms env %d \n", test.nb_test);

		ft_test_ifcmp_printsplit(tSplit.env_tmp, g_ms.env_tmp);
		ft_test_ifcmp_printsplit(tSplit.argv_end, g_ms.argv);
		ft_test_if_streq(test.print, g_test_buffer);
		if (ret != test.ret_int)
			printf("ret diff %d // %d \n", test.ret_int, ret);
	}

	// free
	ms_free(g_ms.env);
	ms_free(g_ms.env_tmp);
	test_free(&tSplit);
}

void new_test_all()
{
	g_test = 1;
	new_passed_test();

}