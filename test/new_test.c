
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


void new_test_all()
{
	g_test = 1;
//	new_passed_test();

	chdir("/Users/adpusel");
	mkdir("test_minishell", 0777);

	char *test_directory = "/Users/adpusel/test_minishell";

	// : [ aa aa aa ]
	test_ms_cd((ms_test) {
	 .nb_test= 25,
	 .argv = "aa aa aa",
	 .start_repository = test_directory,
	 .env = "HOME=/Users/adpusel",
	 .new_env = "HOME=/Users/adpusel",
	 .end_repository = test_directory,
	 .print = MS_BAD_NB_ARG"\n",
	 .ret_int = -1
	});

	// : [ ]
	test_ms_cd((ms_test) {
	 .nb_test = 26,
	 .argv = "",
	 .start_repository = "/",
	 .env = "HOME=/Users/adpusel",
	 .new_env = "HOME=/Users/adpusel OLDPATH=/",
	 .end_repository = "/Users/adpusel",
	 .print = ""
	});

	// [ -- ]
	test_ms_cd((ms_test) {
	 .nb_test = 27,
	 .argv = "--",
	 .start_repository = "/Users",
	 .env = "HOME=/Users/adpusel OLDPATH=aoeuaoeu",
	 .new_env = "HOME=/Users/adpusel OLDPATH=/Users",
	 .end_repository = "/Users/adpusel",
	 .print = ""
	});

	// [ -- ] + no $HOME
	test_ms_cd((ms_test) {
	 .nb_test = 28,
	 .argv = "",
	 .start_repository = "/Users",
	 .env = "OLDPATH=",
	 .new_env = "OLDPATH=",
	 .end_repository = "/Users",
	 .print = MS_CD_NO_HOME"\n",
	 .ret_int = -1
	});


	// : [ - ]
	test_ms_cd((ms_test) {
	 .nb_test = 29,
	 .argv = "-",
	 .start_repository = "/Users",
	 .env = "OLDPATH=/Users/adpusel",
	 .new_env = "OLDPATH=/Users",
	 .end_repository = "/Users/adpusel",
	 .print = "/Users/adpusel\n",
	 .ret_int = 0
	});

	// : [ - ] + no $OLDPATH
	test_ms_cd((ms_test) {
	 .nb_test = 30,
	 .argv = "-",
	 .start_repository = "/Users",
	 .env = "",
	 .new_env = "",
	 .end_repository = "/Users",
	 .print = MS_CD_NO_OLDPATH"\n",
	 .ret_int = -1
	});

	// : [ . ]
	test_ms_cd((ms_test) {
	 .nb_test = 31,
	 .argv = ".",
	 .start_repository = "/Users",
	 .env = "OLDPATH=/Users/adpusel",
	 .new_env = "OLDPATH=/Users",
	 .end_repository = "/Users",
	 .print = "",
	 .ret_int = 0
	});

	// : [ /file/test ]
	test_ms_cd((ms_test) {
	 .nb_test = 32,
	 .argv = "/Users/adpusel",
	 .start_repository = "/Users",
	 .env = "OLDPATH=/Users/adpusel",
	 .new_env = "OLDPATH=/Users",
	 .end_repository = "/Users/adpusel",
	 .print = "",
	 .ret_int = 0
	});

	// : [ /Users/ ]
	test_ms_cd((ms_test) {
	 .nb_test = 33,
	 .argv = "/Users/",
	 .start_repository = "/Users",
	 .env = "OLDPATH=/Users/adpusel",
	 .new_env = "OLDPATH=/Users",
	 .end_repository = "/Users",
	 .print = "",
	 .ret_int = 0
	});

	// : [ .. ]
	test_ms_cd((ms_test) {
	 .nb_test = 34,
	 .argv = "..",
	 .start_repository = "/Users/adpusel",
	 .env = "",
	 .new_env = "OLDPATH=/Users/adpusel",
	 .end_repository = "/Users",
	 .print = "",
	 .ret_int = 0
	});

	// : [ .././adpusel ]
	test_ms_cd((ms_test) {
	 .nb_test = 35,
	 .argv = ".././adpusel",
	 .start_repository = "/Users/adpusel",
	 .env = "",
	 .new_env = "OLDPATH=/Users/adpusel",
	 .end_repository = "/Users/adpusel",
	 .print = "",
	 .ret_int = 0
	});


	// : [  ] file not exist
	test_ms_cd((ms_test) {
	 .nb_test = 36,
	 .argv = "../asoeuth",
	 .start_repository = "/Users/adpusel",
	 .end_repository = "/Users/adpusel",
	 .env = "",
	 .new_env = "",
	 .print = "cd: no such file or directory: ../asoeuth\n",
	 .ret_int = -1
	});


	// : [ file ] no access
	chdir("/Users/adpusel");
	mkdir("test-cd-000", 0);

	test_ms_cd((ms_test) {
	 .nb_test = 37,
	 .argv = "test-cd-000",
	 .start_repository = "/Users/adpusel",
	 .end_repository = "/Users/adpusel",
	 .env = "",
	 .new_env = "",
	 .print = "cd: permission denied: test-cd-000\n",
	 .ret_int = -1
	});



//	char **t1 = ft_strsplit("$1 ", " ");
//	g_ms.env = ft_strsplit("1=toto", " ");
//
//	replace_jocker(t1);




}