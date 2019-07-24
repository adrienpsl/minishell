
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
	char buffer_end_repository[10000];

	chdir(test.start_repository);
	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	ms_init(tSplit.env);

	// function tested
	g_ms.argv = tSplit.argv;
	g_ms.argv_size = ft_strsplit_count(g_ms.argv);
	ret = ms_cd();

	getcwd(buffer_end_repository, 5000);

	// print error
	if (
	 !ft_streq(test.print, g_test_buffer) ||
	 !ft_streq(test.end_repository, buffer_end_repository) ||
	 ft_strsplit_cmp(tSplit.new_env, g_ms.env) ||
	 ret != test.ret_int
	 )
	{
		printf("ms env %d *******************************\n", test.nb_test);
		ft_test_if_streq(test.end_repository, buffer_end_repository, "end_repo");
		ft_test_if_streq(test.print, g_test_buffer, "print");
		ft_test_ifcmp_printsplit(tSplit.new_env, g_ms.env, "new_env");
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

	char *test_directory = "/Users/adpusel/test_minishell";
	(void) test_directory;

	chdir("/Users/adpusel");
	mkdir("test_minishell", 0777);

//	// : [ aa aa aa ]
//	test_ms_cd((ms_test) {
//	 .nb_test= 25,
//	 .argv = "aa aa aa",
//	 .start_repository = test_directory,
//	 .env = "HOME=/Users/adpusel",
//	 .new_env = "HOME=/Users/adpusel",
//	 .end_repository = test_directory,
//	 .print = MS_BAD_NB_ARG"\n",
//	 .ret_int = -1
//	});
//
//	// : [ ]
//	test_ms_cd((ms_test) {
//	 .nb_test = 26,
//	 .argv = "",
//	 .start_repository = "/",
//	 .env = "HOME=/Users/adpusel",
//	 .new_env = "HOME=/Users/adpusel OLDPATH=/",
//	 .end_repository = "/Users/adpusel",
//	 .print = ""
//	});
//
//	// [ -- ]
//	test_ms_cd((ms_test) {
//		.nb_test = 27,
//		.argv = "--",
//		.start_repository = "/Users",
//		.env = "HOME=/Users/adpusel OLDPATH=aoeuaoeu",
//		.new_env = "HOME=/Users/adpusel OLDPATH=/Users",
//		.end_repository = "/Users/adpusel",
//		.print = ""
//	});
//
//	// [ -- ] + no $HOME
//	test_ms_cd((ms_test) {
//		.nb_test = 28,
//		.argv = "",
//		.start_repository = "/Users",
//		.env = "OLDPATH=",
//		.new_env = "OLDPATH=",
//		.end_repository = "/Users",
//		.print = MS_CD_NO_HOME"\n",
//		.ret_int = -1
//	});
//
//
//	// [ - ]
//	test_ms_cd((ms_test) {
//		.nb_test = 29,
//		.argv = "-",
//		.start_repository = "/Users",
//		.env = "OLDPATH=/Users/adpusel",
//		.new_env = "OLDPATH=/Users",
//		.end_repository = "/Users/adpusel",
//		.print = "/Users/adpusel\n",
//		.ret_int = 0
//	});
//
//	// test cd - no oldpath
//	test_ms_cd((ms_test) {
//		.nb_test = 29,
//		.argv = "-",
//		.start_repository = "/Users",
//		.env = "OLDPATH=/Users/adpusel",
//		.new_env = "OLDPATH=/Users",
//		.end_repository = "/Users/adpusel",
//		.print = "/Users/adpusel\n",
//		.ret_int = 0
//	});

	// test cd .
	test_ms_cd((ms_test) {
		.nb_test = 30,
		.argv = ".",
		.start_repository = "/Users",
		.env = "OLDPATH=/Users/adpusel",
		.new_env = "OLDPATH=/Users",
		.end_repository = "/Users",
		.print = "",
		.ret_int = 0
	});

	// test cd /file/test

	// test cd ./file/test

	// test cd file1 fileNoExist

	// test cd file1 file2

	// test cd file

	// test cd no acces

	// test cd no exist

	// bad option

}