#include <libft.h>
#include <minishell.h>
#include "test.h"

#include <libft.h>
#include <minishell.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "test.h"

/* test utils ------------------------------------------------------------ */
void test_free(t_split *split)
{
	if (split->env)
		ft_strsplit_free(&split->env);
	if (split->argv)
		ft_strsplit_free(&split->argv);
	if (split->new_env)
		ft_strsplit_free(&split->env);
	if (split->env_tmp)
		ft_strsplit_free(&split->env_tmp);
}

void test_do_split(ms_test *test, t_split *split)
{
	ft_bzero(split, sizeof(t_split));
	if (test->env)
		split->env = ft_strsplit(test->env, " ");
	if (test->argv)
		split->argv = ft_strsplit(test->argv, " ");
	if (test->new_env)
		split->new_env = ft_strsplit(test->new_env, " ");
	if (test->env_tmp)
		split->env_tmp = ft_strsplit(test->env_tmp, " ");
	if (test->argv_end)
		split->argv_end = ft_strsplit(test->argv_end, " ");
}

void test_set_fd(char *str)
{
	int fd;
	chdir("/Users/adpusel/code/42/minishell");
	mkdir("test_files", 0777);
	fclose(fopen("test_files/current_test", "w"));
	fd = open("test_files/current_test", O_CREAT | O_RDWR);
	write(fd, str, strlen(str));
	g_fd = open("test_files/current_test", O_RDONLY);
}

/* function ------------------------------------------------------------ */

void test_ms_init(ms_test test)
{
	// init
	t_split s;
	test_do_split(&test, &s);

	g_env = ft_strsplit(test.env, " ");
	// print error
	if (ft_strsplit_cmp(g_env, s.env))
	{
		printf("Ms init %d \n", test.nb_test);
		ft_test_ifcmp_printsplit(g_env, s.env, NULL);
	}

	// free
	ft_strsplit_free(&g_env);;
	test_free(&s);
}

void test_ms_env_add(ms_test test)
{
	// init
	t_split tSplit;
	int ret;

	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	g_env = ft_strsplit(test.env, " ");

	// function tested
	char **argv = tSplit.argv;
	ret = ms_setenv(argv);

	// print error
	if (
	 ft_strsplit_cmp(tSplit.new_env, g_env) ||
	 !ft_streq(test.print, g_test_buffer) ||
	 ret != test.ret_int
	 )
	{
		printf("ms_setenv %d ***************************\n", test.nb_test);

		ft_test_ifcmp_printsplit(tSplit.new_env, g_env, NULL);
		ft_test_if_streq(test.print, g_test_buffer, NULL);
		if (ret != test.ret_int)
			printf("ret diff %d // %d \n", test.ret_int, ret);
	}

	// free
	ft_strsplit_free(&g_env);;
	test_free(&tSplit);
}
void test_ms_unsetenv(ms_test test)
{
	// init
	t_split tSplit;
	int ret;

	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	g_env = ft_strsplit_copy(tSplit.env, 0);

	// function tested
	ret = ms_unsetenv(tSplit.argv, g_env);

	// print error
	if (
	 ft_strsplit_cmp(tSplit.new_env, g_env) ||
	 !ft_streq(test.print, g_test_buffer) ||
	 ret != test.ret_int
	 )
	{
		printf("ms env add %d \n", test.nb_test);

		ft_test_ifcmp_printsplit(tSplit.new_env, g_env, NULL);
		ft_test_if_streq(test.print, g_test_buffer, NULL);
		if (ret != test.ret_int)
			printf("ret diff %d // %d \n", test.ret_int, ret);
	}

	// free
	ft_strsplit_free(&g_env);;
	test_free(&tSplit);
}

void test_ms_env(ms_test test)
{
	// init
	t_split tSplit;
	char **new_argv;

	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	g_env = ft_strsplit_copy(tSplit.env, 0);
	char **real_env;

	// function tested
	new_argv = ms_env(tSplit.argv, &real_env);

	// print error
	if (
	 ft_strsplit_cmp(tSplit.env_tmp, g_env) ||
	 ft_strsplit_cmp(tSplit.argv_end, new_argv) ||
	 !ft_streq(test.print, g_test_buffer)
	 )
	{
		printf("ms env %d \n", test.nb_test);

		ft_test_ifcmp_printsplit(tSplit.env_tmp, g_env, NULL);
		ft_test_ifcmp_printsplit(tSplit.argv_end, new_argv, NULL);
		ft_test_if_streq(test.print, g_test_buffer, NULL);
	}

	// free
	ft_strsplit_free(&g_env);
	ft_strsplit_free(&real_env);
	test_free(&tSplit);
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
	g_env = ft_strsplit_copy(tSplit.env, 0);

	// function tested
	ret = ms_cd(tSplit.argv);

	getcwd(buffer_end_repository, 5000);

	// print error
	if (
	 !ft_streq(test.print, g_test_buffer) ||
	 !ft_streq(test.end_repository, buffer_end_repository) ||
	 ft_strsplit_cmp(tSplit.new_env, g_env) ||
	 ret != test.ret_int
	 )
	{
		printf("ms env %d *******************************\n", test.nb_test);
		ft_test_if_streq(test.end_repository, buffer_end_repository,
						 "end_repo");
		ft_test_if_streq(test.print, g_test_buffer, "print");
		ft_test_ifcmp_printsplit(tSplit.new_env, g_env, "new_env");
		if (ret != test.ret_int)
			printf("ret diff %d // %d \n", test.ret_int, ret);
	}

	// free
	ft_strsplit_free(&g_env);
	test_free(&tSplit);
}

void test_ms_parser(ms_test test)
{
	// init
	t_split tSplit;
	int ret;

	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	ft_strsplit_free(&tSplit.argv);
	tSplit.argv = ft_strsplit(test.argv, "|");
	g_env = ft_strsplit_copy(tSplit.env, 0);

	test_set_fd(test.line);

	// function tested
	char **argv;
	ret = ms_parser(&argv);


	// print error
	if (
	 ft_strsplit_cmp(tSplit.argv, argv) ||
	 ret != test.ret_int
	 )
	{
		printf("ms env %d *******************************\n", test.nb_test);
		ft_test_ifcmp_printsplit(tSplit.argv, argv, "new_env");
		if (ret != test.ret_int)
			printf("ret diff %d // %d \n", test.ret_int, ret);
	}

	// free
	ft_strsplit_free(&g_env);
	test_free(&tSplit);
}

void test_ms_find_binary(ms_test test)
{
	t_split tSplit;
	char *binary_path;

	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	g_env = ft_strsplit_copy(tSplit.env, 0);

	// binary path
	binary_path = ms_find_binary(test.binary_name);

	// say if I find it
	if (!ft_streq(test.binary_path, binary_path))
	{
		printf("ms env %d *******************************\n", test.nb_test);
		ft_test_if_streq(test.binary_path, binary_path, "binary find");
	}
}

void test_ms_handle_binary(ms_test test)
{
	t_split tSplit;
	int ret;

	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	g_env = ft_strsplit_copy(tSplit.env, 0);

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
	ft_strsplit_free(&g_env);;
	test_free(&tSplit);
}

/* all test passed ------------------------------------------------------------ */
void new_passed_test()
{
	test_ms_init((ms_test) {
	 .env = "toto=titi"
	});

	char *env_star = "toto=titi";
	(void) env_star;


	// too much argv
	test_ms_env_add((ms_test) {
	 .nb_test = 0,
	 .env = env_star,
	 .argv = "titi tata toto",
	 .print = MS_BAD_NB_ARG"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});

	// no argv
	test_ms_env_add((ms_test) {
	 .nb_test = 1,
	 .env = env_star,
	 .argv = "",
	 .print = MS_BAD_NB_ARG"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});

	//	 forbidden char
	test_ms_env_add((ms_test) {
	 .nb_test = 2,
	 .env = env_star,
	 .argv = "toto titi$",
	 .print = MS_SETENV_FORBIDDEN_CHAR"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});

	test_ms_env_add((ms_test) {
	 .nb_test = 3,
	 .env = env_star,
	 .argv = "toto$titi",
	 .print = MS_SETENV_FORBIDDEN_CHAR"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});

	test_ms_env_add((ms_test) {
	 .nb_test = 4,
	 .env = env_star,
	 .argv = "toto= titi",
	 .print = MS_SETENV_FORBIDDEN_CHAR"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});

	test_ms_env_add((ms_test) {
	 .nb_test = 5,
	 .env = env_star,
	 .argv = "toto ti=ti",
	 .print = MS_SETENV_FORBIDDEN_CHAR"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});

	test_ms_env_add((ms_test) {
	 .nb_test = 6,
	 .env = env_star,
	 .new_env = env_star,
	 .argv = "toto=titi=",
	 .print = MS_SETENV_FORBIDDEN_CHAR"\n",
	 .ret_int = -1
	});

	test_ms_env_add((ms_test) {
	 .nb_test = 7,
	 .env = "toto=fil tata=titi super=manger faire=chips",
	 .new_env = "toto=fil tata=titi super=manger faire=chips toata=titi",
	 .argv = "toata titi",
	 .print = "",
	 .ret_int = 0
	});

	// good and add
	char *full_env = "a1=toto a2=titi a3=tata";
	test_ms_env_add((ms_test) {
	 .nb_test = 8,
	 .env = full_env,
	 .new_env = "a1=toto a2=titi a3=tata new=add",
	 .argv = "new=add",
	 .print = "",
	 .ret_int = 0
	});

	// good and replace
	test_ms_env_add((ms_test) {
	 .nb_test = 9,
	 .env = "a1=toto a2=titi a3=tata",
	 .new_env = "a2=titi a3=tata a1=lalala",
	 .argv = "a1=lalala",
	 .print = "",
	 .ret_int = 0
	});

	test_ms_env_add((ms_test) {
	 .nb_test = 10,
	 .env = "a1=toto a2=titi a3=tata",
	 .new_env = "a1=toto a2=titi a3=hohoho",
	 .argv = "a3=hohoho",
	 .print = "",
	 .ret_int = 0
	});

	/* unsetenv ------------------------------------------------------------ */
	// to much argv
	test_ms_unsetenv((ms_test) {
	 .nb_test = 11,
	 .env = "",
	 .argv = "titi tata toto",
	 .print = "env : too many arguments\n",
	 .new_env = "",
	 .ret_int = -1
	});

	// few argv
	test_ms_unsetenv((ms_test) {
	 .nb_test = 12,
	 .env = "",
	 .argv = "",
	 .print = "env : too many arguments\n",
	 .new_env = "",
	 .ret_int = -1
	});

	// key not in env
	test_ms_unsetenv((ms_test) {
	 .nb_test = 13,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv = "a",
	 .print = "",
	 .new_env = "a1=toto a2=titi a3=tata",
	 .ret_int = 0
	});

	// same
	test_ms_unsetenv((ms_test) {
	 .nb_test = 14,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv = "toto",
	 .print = "",
	 .new_env = "a1=toto a2=titi a3=tata",
	 .ret_int = 0
	});

	// delete first
	test_ms_unsetenv((ms_test) {
	 .nb_test = 15,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv = "a1",
	 .print = "",
	 .new_env = "a2=titi a3=tata",
	 .ret_int = 0
	});

	// middle
	test_ms_unsetenv((ms_test) {
	 .nb_test = 16,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv = "a2",
	 .print = "",
	 .new_env = "a1=toto a3=tata",
	 .ret_int = 0
	});

	// end
	test_ms_unsetenv((ms_test) {
	 .nb_test = 17,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv = "a3",
	 .print = "",
	 .new_env = "a1=toto a2=titi",
	 .ret_int = 0
	});

	// one
	test_ms_unsetenv((ms_test) {
	 .nb_test = 18,
	 .env = "a1=toto",
	 .argv = "a1",
	 .print = "",
	 .new_env = "",
	 .ret_int = 0
	});

	/* env ------------------------------------------------------------ */
	//	 test env null
	test_ms_env((ms_test) {
	 .nb_test = 19,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv_end = "",
	 .env_tmp = "",
	 .argv = "",
	 .print = "a1=toto\na2=titi\na3=tata\n",
	 .ret_int = 0
	});

	// test env -i
	test_ms_env((ms_test) {
	 .nb_test = 20,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv_end = "",
	 .env_tmp = "",
	 .argv = "-i",
	 .print = "\n",
	 .ret_int = 0
	});

	// env -i and option
	test_ms_env((ms_test) {
	 .nb_test = 21,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv_end = "ls",
	 .env_tmp = "",
	 .argv = "-i ls",
	 .print = "",
	 .ret_int = 0
	});

	test_ms_env((ms_test) {
	 .nb_test = 22,
	 .env = "a1=toto a2=titi a3=tata",
	 .env_tmp = "a1=toto a2=titi a3=tata",
	 .argv = "-u",
	 .argv_end = "",
	 .print = "a1=toto\na2=titi\na3=tata\n",
	 .ret_int = 0
	});

	// test env -u --
	test_ms_env((ms_test) {
	 .nb_test = 23,
	 .env = "a1=toto a2=titi a3=tata",
	 .env_tmp = "a2=titi a3=tata",
	 .argv = "-u a1",
	 .argv_end = "",
	 .print = "a2=titi\na3=tata\n",
	 .ret_int = 0
	});

	test_ms_env((ms_test) {
	 .nb_test = 24,
	 .env = "a1=toto a2=titi a3=tata",
	 .env_tmp = "a1=toto a2=titi a3=tata",
	 .argv = "-u sp",
	 .argv_end = "",
	 .print = "a1=toto\na2=titi\na3=tata\n",
	 .ret_int = 0
	});

	/* cd test ------------------------------------------------------------ */

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
	 .print = "The env variable : HOME is no set.\n",
	 .ret_int = -1
	});


	// : [ - ]
	test_ms_cd((ms_test) {
	 .nb_test = 29,
	 .argv = "-",
	 .start_repository = "/Users",
	 .env = "OLDPATH=/Users/adpusel HOME=/Users/adpusel",
	 .new_env = "HOME=/Users/adpusel OLDPATH=/Users",
	 .end_repository = "/Users/adpusel",
	 .print = "~\n",
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
	 .print = "The env variable : OLDPATH is no set.\n",
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


	// : [ file file ]
	chdir("/Users/adpusel");

	mkdir("test-cd-1", 0777);
	mkdir("test-cd-2", 0777);

	mkdir("test-cd-1/dir_1", 0777);
	mkdir("test-cd-2/dir_1", 0777);

	test_ms_cd((ms_test) {
	 .nb_test = 38,
	 .argv = "test-cd-1 test-cd-2",
	 .start_repository = "/Users/adpusel/test-cd-1/dir_1",
	 .end_repository = "/Users/adpusel/test-cd-2/dir_1",
	 .env = "HOME=/Users/adpusel",
	 .new_env = "HOME=/Users/adpusel OLDPATH=/Users/adpusel/test-cd-1/dir_1",
	 .print = "~/test-cd-2/dir_1\n",
	 .ret_int = 0
	});


	// : [ file no-exist ]
	chdir("/Users/adpusel");

	mkdir("test-cd-1", 0777);
	mkdir("test-cd-2", 0777);

	mkdir("test-cd-1/dir_1", 0777);
	mkdir("test-cd-2/dir_1", 0777);

	test_ms_cd((ms_test) {
	 .nb_test = 39,
	 .argv = "test-cd-1 test-cd-",
	 .start_repository = "/Users/adpusel/test-cd-1/dir_1",
	 .end_repository = "/Users/adpusel/test-cd-1/dir_1",
	 .env = "HOME=/Users/adpusel",
	 .new_env = "HOME=/Users/adpusel",
	 .print = "cd: no such file or directory: /Users/adpusel/test-cd-/dir_1\n",
	 .ret_int = -1
	});

	// : [ file no-access ]
	chdir("/Users/adpusel");

	mkdir("test-cd-1", 0777);
	mkdir("test-cd-2", 0777);

	mkdir("test-cd-1/dir_1", 0777);
	mkdir("test-cd-2/dir_1", 0777);

	mkdir("test-cd-1/dir_2", 0777);
	mkdir("test-cd-2/dir_2", 0000);

	test_ms_cd((ms_test) {
	 .nb_test = 40,
	 .argv = "test-cd-1 test-cd-2",
	 .start_repository = "/Users/adpusel/test-cd-1/dir_2",
	 .end_repository = "/Users/adpusel/test-cd-1/dir_2",
	 .env = "",
	 .new_env = "",
	 .print = "cd: permission denied: /Users/adpusel/test-cd-2/dir_2\n",
	 .ret_int = -1
	});

	// : [ file .. ]
	chdir("/Users/adpusel");

	mkdir("test-cd-1", 0777);
	mkdir("test-cd-2", 0777);

	mkdir("test-cd-1/dir_1", 0777);
	mkdir("test-cd-2/dir_1", 0777);

	mkdir("test-cd-1/dir_2", 0777);
	mkdir("test-cd-2/dir_2", 0000);

	test_ms_cd((ms_test) {
	 .nb_test = 40,
	 .argv = "/Users/adpusel ..",
	 .start_repository = "/Users/adpusel/test-cd-1/dir_2",
	 .end_repository = "/Users/adpusel/test-cd-1/dir_2",
	 .env = "",
	 .new_env = "",
	 .print = "cd: no such file or directory: ../test-cd-1/dir_2\n",
	 .ret_int = -1
	});

	/* test parser ------------------------------------------------------------ */

	// : [ \n ]
	test_ms_parser((ms_test) {
	 .nb_test = 41,
	 .env = "",
	 .argv = "",
	 .line = "\n",
	 .ret_int = 0
	});

	// : [ '' \n ]
	test_ms_parser((ms_test) {
	 .nb_test = 42,
	 .env = "",
	 .argv = "",
	 .line = "'' \n",
	 .ret_int = 0
	});


	// : [ 'a' \n ]
	test_ms_parser((ms_test) {
	 .nb_test = 43,
	 .env = "",
	 .line = "'a' \n",
	 .argv = "a",
	 .ret_int = 0
	});

	test_ms_parser((ms_test) {
	 .nb_test = 44,
	 .env = "",
	 .line = "'a \"' \n",
	 .argv = "a \"",
	 .ret_int = 0
	});

	test_ms_parser((ms_test) {
	 .nb_test = 45,
	 .env = "",
	 .line = "'a \"' a b c\n",
	 .argv = "a \"|a|b|c",
	 .ret_int = 0
	});

	test_ms_parser((ms_test) {
	 .nb_test = 46,
	 .env = "",
	 .line = "'a \"' a b c \"oooo\'\'\'\'\'\'\"\n",
	 .argv = "a \"|a|b|c|oooo\'\'\'\'\'\'",
	 .ret_int = 0
	});

	test_ms_parser((ms_test) {
	 .nb_test = 47,
	 .env = "",
	 .line = "'a \"' a b c \"oooo\'\'\'\'\'\'\"\n",
	 .argv = "a \"|a|b|c|oooo\'\'\'\'\'\'",
	 .ret_int = 0
	});

	test_ms_parser((ms_test) {
	 .nb_test = 48,
	 .env = "TOTO=heyman",
	 .line = "$TOTO",
	 .argv = "heyman",
	 .ret_int = 0
	});

	test_ms_parser((ms_test) {
	 .nb_test = 49,
	 .env = "TOTO=heyman tata=tata titi=titi",
	 .line = "$TOTO $tata $titi",
	 .argv = "heyman|tata|titi",
	 .ret_int = 0
	});

	test_ms_parser((ms_test) {
	 .nb_test = 50,
	 .env = "TOTO=heyman tata=tata titi=titi HOME=a",
	 .line = "~",
	 .argv = "a",
	 .ret_int = 0
	});

	test_ms_parser((ms_test) {
	 .nb_test = 51,
	 .env = "TOTO=heyman tata=tata titi=titi HOME=a",
	 .line = "$TOTO $tata $titi ~ ~",
	 .argv = "heyman|tata|titi|a|a",
	 .ret_int = 0
	});

	test_ms_parser((ms_test) {
	 .nb_test = 52,
	 .env = "TOTO=heyman tata=tata titi=titi HOME=a",
	 .line = "faire du $TOTO -",
	 .argv = "faire|du|heyman|-",
	 .ret_int = 0
	});

	test_ms_parser((ms_test) {
	 .nb_test = 53,
	 .env = "TOTO=heyman tata=tata titi=titi HOME=home/toto",
	 .line = "faire du $TOTO -- ~/et voila",
	 .argv = "faire|du|heyman|--|home/toto/et|voila",
	 .ret_int = 0
	});

	/* test ms_find_binary ------------------------------------------------------------ */
	// if no path
	test_ms_find_binary((ms_test) {
	 .nb_test = 54,
	 .env = "",
	 .binary_name = "",
	 .binary_path = NULL
	});

	// if has binary
	test_ms_find_binary((ms_test) {
	 .nb_test = 55,
	 .env = "PATH=/bin",
	 .binary_name = "ls",
	 .binary_path = "/bin/ls"
	});

	test_ms_find_binary((ms_test) {
	 .nb_test = 56,
	 .env = "PATH=/bi:/Users/adpusel/code/42/minishell/prg",
	 .binary_name = "pgr_print_name",
	 .binary_path = "/Users/adpusel/code/42/minishell/prg/pgr_print_name"
	});

	// no binary
	test_ms_find_binary((ms_test) {
	 .nb_test = 57,
	 .env = "",
	 .binary_name = "PATH=/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/.nvm/versions/node/v10.15.3/bin:/Users/adpusel/code/mongodb/bin:/usr/local/bin:/usr/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools",
	 .binary_path = NULL
	});

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
