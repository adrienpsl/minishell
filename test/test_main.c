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

#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"

void test_get_env_variable(char *line, char **env, int end, char *res, int test);
void test_replace_env_variable(char *line, char **env, char *res, int test);
void test_ms_cd(char **env, char **arg, char **new_env, int ret, char *curpath, char *error_text, int test);
void find_binary_test(char *name, char **env, char *res, int test);
void test_ms_env_copy(char *env_str, int ret, int error, int test);
void test_ms_env_add(char *env, char *new_var, int ret, char *res, char *error_str, int test);
void test_ms_env_remove(char **env,
 char *deleting_key, int ret, char **res, int error, int test);
void test_ms_get_env_value(char **env, char *key, char *ret, int test);
void test_ms_env_modify(char **env, char *key, char *new_value, int ret, char **res, int test);
void test_quote(char *str, int res, int *test);
void test_get_all_commands(char *name_file, char *res, int test);
void write_in_file(char *str);
void test_get_all_command(char *test_str, char *res, int *test);
void test_transform_space(char *str, char *res, int test);
void test_read_command(char *command, char *res, int test);
void echo_test(char *line, char *res, int test);

void tested_test()
{
	g_test = 1;

	/* env copy ------------------------------------------------------------ */
	test_ms_env_copy("", 0, 0, 1);
	test_ms_env_copy("toto=super mimi=toto superTest", 0, 0, 2);

	/* env add testing ------------------------------------------------------------ */
	// lack of data
	test_ms_env_add("", "", -1, NULL, "Bad number argument given to set env\n", 3);
	test_ms_env_add("toto=tata", "", -1, NULL, "Bad number argument given to set env\n", 4);
	test_ms_env_add("", "toto=tata", 0, "toto=tata", "", 5);
	// = pb
	test_ms_env_add("", "tototata", -1, "", "The env separator is one single =\n", 6);
	test_ms_env_add("tata=toto", "toto=tata=", -1, "tata=toto", "The env separator is one single =\n", 7);
	test_ms_env_add("tata=toto", "super= titi", -1, "tata=toto", "If two elements are supply no =\n", 81);
	test_ms_env_add("tata=toto", "super =titi=", -1, "tata=toto", "If two elements are supply no =\n", 82);
	// $ pb
	test_ms_env_add("tata=toto", "super=$manger", -1, "tata=toto", "No $ en env variable\n", 83);
	test_ms_env_add("tata=toto", "super $manger", -1, "tata=toto", "No $ en env variable\n", 84);
	// good
	test_ms_env_add("tata=toto", "super=titi", 0, "tata=toto super=titi", "", 8);

	// no env
	char *env_88[2] = { NULL };
	char *res_88[2] = { NULL };
	test_ms_env_remove(env_88, "toto", -1, res_88, 0, 88);

	// no key
	char *env_9[2] = { NULL };
	char *res_9[2] = { NULL };
	test_ms_env_remove(env_9, NULL, -1, res_9, 0, 9);

	// no key and env
	char *env_10[2] = { "toto=titi" };
	test_ms_env_remove(env_10, NULL, -1, env_10, 0, 10);

	// delete one
	char *env_11[2] = { "toto=tata" };
	char *res_11[2] = { NULL };
	test_ms_env_remove(env_11, "toto", 0, res_11, 0, 11);

	// delete middle
	char *env_12[5] = { "suer=aaoeu", "toto=tata", "manger=chipes", "aaaaaaa", NULL };
	char *res_12[5] = { "suer=aaoeu", "manger=chipes", "aaaaaaa", NULL };
	test_ms_env_remove(env_12, "toto", 0, res_12, 0, 12);

	// delete end
	char *env_13[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	char *res_13[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", NULL };
	test_ms_env_remove(env_13, "manger", 0, res_13, 0, 13);

	// no bad
	char *env_14[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	test_ms_get_env_value(env_14, "mange", NULL, 14);

	// null key
	char *env_15[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	test_ms_get_env_value(env_15, NULL, NULL, 15);

	// good key
	char *env_16[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	test_ms_get_env_value(env_16, "suer", "aaoeu", 16);

	// good key
	char *env_17[5] = { "suer=aaoeu", "toto=", "aaaaaaa", "manger=chipes", NULL };
	test_ms_get_env_value(env_17, "toto", "", 17);

	//	test ms_env_modify
	char *env_117[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	char *res_117[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=titi", NULL };
	test_ms_env_modify(env_117, "manger", "titi", 0, res_117, 117);

	char *env_19[2] = { "OLDPATH=/Users/adpusel", NULL };
	char *new_env_19[2] = { "OLDPATH=/Users/adpusel/code/42/minishell/cmake-build-debug", NULL };
	char *argv_19[3] = { "-", NULL };
	test_ms_cd(env_19, argv_19, new_env_19, 0, "/Users/adpusel", "", 19);

	char *env_20[3] = { "OLDPATH=/Users/adpusel/code/42/minishell/cmake-build-debug", NULL };
	char *argv_20[3] = { "--", "-", NULL };
	char *new_env_20[2] = { "OLDPATH=/Users/adpusel", NULL };
	test_ms_cd(env_20, argv_20, new_env_20, 0, "/Users/adpusel/code/42/minishell/cmake-build-debug", "", 20);

	char *env_21[3] = { "OLDPATH=/Users/adpusel/code/42/minishell/cmake-build-debug", NULL };
	char *argv_21[3] = { "/Users/adpusel", NULL };
	char *new_env_21[2] = { "OLDPATH=/Users/adpusel/code/42/minishell/cmake-build-debug", NULL };
	test_ms_cd(env_21, argv_21, new_env_21, 0, "/Users/adpusel", "", 21);

	chdir("/Users/adpusel");
	char *env_22[3] = { "OLDPATH=/toto", NULL };
	char *argv_22[3] = { "--", "/Users/adpusel/code", NULL };
	char *new_env_22[2] = { "OLDPATH=/Users/adpusel", NULL };
	test_ms_cd(env_22, argv_22, new_env_22, 0, "/Users/adpusel/code", "", 22);

	chdir("/Users/adpusel");
	char *env_23[3] = { "OLDPATH=/toto", NULL };
	char *argv_23[3] = { "--", "./code", NULL };
	char *new_env_23[2] = { "OLDPATH=/Users/adpusel", NULL };
	test_ms_cd(env_23, argv_23, new_env_23, 0, "/Users/adpusel/./code", "", 23);

	chdir("/Users/adpusel");
	char *env_24[3] = { "OLDPATH=/toto", NULL };
	char *argv_24[3] = { "..", NULL };
	char *new_env_24[2] = { "OLDPATH=/Users/adpusel", NULL };
	test_ms_cd(env_24, argv_24, new_env_24, 0, "/Users/adpusel/..", "", 24);

	chdir("/Users/adpusel");
	char *env_25[3] = { "OLDPATH=/toto", NULL };
	char *argv_25[3] = { "..", NULL };
	char *new_env_25[2] = { "OLDPATH=/Users/adpusel", NULL };
	test_ms_cd(env_25, argv_25, new_env_25, 0, "/Users/adpusel/..", "", 25);

	chdir("/Users/adpusel");
	char *env_26[3] = { "OLDPATH=/toto", NULL };
	char *argv_26[3] = { "--", "..", NULL };
	char *new_env_26[2] = { "OLDPATH=/Users/adpusel", NULL };
	test_ms_cd(env_26, argv_26, new_env_26, 0, "/Users/adpusel/..", "", 26);


	// test change end file
	chdir("/Users/adpusel/code");
	char *env_27[3] = { "OLDPATH=/toto", NULL };
	char *argv_27[4] = { "--", "code", "toto", NULL };
	char *new_env_27[2] = { "OLDPATH=/Users/adpusel/code", NULL };
	test_ms_cd(env_27, argv_27, new_env_27, 0, "/Users/adpusel/toto", "", 27);

	// test change middle file
	chdir("/Users/adpusel/toto/t2/t1_1/t2_1");
	char *env_28[3] = { "OLDPATH=/toto", NULL };
	char *argv_28[3] = { "t2", "t1", NULL };
	char *new_env_28[2] = { "OLDPATH=/Users/adpusel/toto/t2/t1_1/t2_1", NULL };
	test_ms_cd(env_28, argv_28, new_env_28, 0, "/Users/adpusel/toto/t1/t1_1/t2_1", "", 28);

	// test change start file
	chdir("/private");
	char *env_29[3] = { "OLDPATH=/toto", NULL };
	char *argv_29[3] = { "/private", "/Users", NULL };
	char *new_env_29[2] = { "OLDPATH=/private", NULL };
	test_ms_cd(env_29, argv_29, new_env_29, 0, "/Users", "", 29);

	// with --
	chdir("/private");
	char *env_30[3] = { "OLDPATH=/toto", NULL };
	char *argv_30[4] = { "--", "/private", "/Users", NULL };
	char *new_env_30[2] = { "OLDPATH=/private", NULL };
	test_ms_cd(env_30, argv_30, new_env_30, 0, "/Users", "", 30);

	// Error, not in path
	chdir("/Users/adpusel/toto");
	char *env_31[3] = { "OLDPATH=/toto", NULL };
	char *argv_31[3] = { "/private", "tata", NULL };
	char *new_env_31[2] = { "OLDPATH=/toto", NULL };
	test_ms_cd(env_31, argv_31, new_env_31, -1, "", "cd: string not in pwd: /private\n", 31);

	// test no argv
	chdir("/Users/adpusel/toto");
	char *env_32[3] = { "HOME=/Users/adpusel", NULL };
	char *argv_32[3] = { NULL };
	char *new_env_32[3] = { "HOME=/Users/adpusel", "OLDPATH=/Users/adpusel/toto", NULL };
	test_ms_cd(env_32, argv_32, new_env_32, 0, "/Users/adpusel", "", 32);

	// home do not exist || old path do not exist
	chdir("/Users/adpusel/toto");
	char *env_33[3] = { "HOME=/Users/adpus", NULL };
	char *argv_33[3] = { "./no_go" };
	char *new_env_33[3] = { "HOME=/Users/adpus", NULL };
	test_ms_cd(env_33, argv_33, new_env_33, -1, "/Users/adpusel/toto/./no_go",
			   "cd: permission denied: /Users/adpusel/toto/./no_go\n", 33);

	// file not exist
	chdir("/Users/adpusel");
	char *env_34[3] = { "HOME=/Users/no_exist", NULL };
	char *argv_34[3] = { NULL };
	char *new_env_34[3] = { "HOME=/Users/no_exist", NULL };
	test_ms_cd(env_34, argv_34, new_env_34, -1, "/Users/no_exist", "cd: no such file or directory: /Users/no_exist\n",
			   34);

	// tes ~
	chdir("/Users");
	char *env_35[3] = { "HOME=/Users/adpusel", NULL };
	char *argv_35[3] = { "~", NULL };
	char *new_env_35[4] = { "HOME=/Users/adpusel", "OLDPATH=/Users", NULL };
	test_ms_cd(env_35, argv_35, new_env_35, 0, "/Users/adpusel", "", 35);

	chdir("/Users");
	char *env_36[3] = { "HOME=/Users/adpul", NULL };
	char *argv_36[3] = { "~", NULL };
	char *new_env_36[4] = { "HOME=/Users/adpul", NULL };
	test_ms_cd(env_36, argv_36, new_env_36, -1, "/Users/adpul", "cd: no such file or directory: /Users/adpul\n", 36);

	int test = 0;
	test_get_all_command("toto et tata a la plag'e\n '", "toto et tata a la plag'e\n '", &test);
	test_get_all_command("''", "''", &test);
	test_get_all_command("'\"\"\"'''", "'\"\"\"'''", &test);
	test_get_all_command("\"\"", "\"\"", &test);
	test_get_all_command("toto et titi ' aoeuaou \n aoue \n aoeuaoeu '1  ' aoeuu \n aoeu \n '",
						 "toto et titi ' aoeuaou \n aoue \n aoeuaoeu '1  ' aoeuu \n aoeu \n '", &test);

	char space_0[20] = " toto ";
	test_transform_space(space_0, " toto ", 0);

	char space_1[20] = "' toto '";
	test_transform_space(space_1, " |toto| ", 1);

	char space_2[20] = "''";
	test_transform_space(space_2, "  ", 2);

	char space_3[200] = " 'd'  aaaa ' oeu'";
	test_transform_space(space_3, "  d   aaaa  |oeu ", 3);

	char space_4[200] = " ' super  te mo fi \" ' aaaa ' oeu'";
	test_transform_space(space_4, "  |super||te|mo|fi|\"|  aaaa  |oeu ", 4);

	char space_5[200] = "' aaaa ' uasdf";
	test_transform_space(space_5, " |aaaa|  uasdf", 5);

	char space_6[200] = "' aaaa ' uasdf";
	test_transform_space(space_6, " |aaaa|  uasdf", 6);

	test_read_command("toto", "toto", 1);
	test_read_command("toto tata", "toto;tata", 2);
	test_read_command("\n", "", 3);
	test_read_command("toto    titi ' sam '", "toto;titi; sam ", 4);
	test_read_command("toto '   titi  '' sam '", "toto;   titi  ; sam ", 5);
	test_read_command("toto '   titi  '' sam \"' \" hy toto ss   '' '' '' ' \" ",
					  "toto;   titi  ; sam \"; hy toto ss   '' '' '' ' ", 6);
	char *get_env_variable[10] = { "SUPER=toto dans la plage", "aouaousths" };
	test_get_env_variable("SUPER aeu", get_env_variable, 5, "toto dans la plage", 1);
	test_get_env_variable("SUPER", get_env_variable, 5, "toto dans la plage", 2);
	test_get_env_variable("", get_env_variable, 5, "", 3);

	char *replacet_env_variable[10] = { "SUPER=a b", "aouaousths", "MANGER=des" };
	test_replace_env_variable("$SUPER aeu", replacet_env_variable, "a b aeu", 1);
	test_replace_env_variable("toto $SUPER", replacet_env_variable, "toto a b", 1);
	test_replace_env_variable("toto $SUPER toto ", replacet_env_variable, "toto a b toto ", 1);
	test_replace_env_variable("toto $SUPER toto $MANGER", replacet_env_variable, "toto a b toto des", 1);
	test_replace_env_variable("toto $SUPER toto $MANGE", replacet_env_variable, "toto a b toto ", 1);
	test_replace_env_variable("toto $SUPER $ toto $MANGE", replacet_env_variable, "toto a b  toto ", 1);
	test_replace_env_variable("toto $SUPER $$ toto $MANGE", replacet_env_variable, "toto a b  toto ", 1);

	/* find binary ------------------------------------------------------------ */
	char *find_binary_env[3] = {
	 "PATH=/Users/adpusel/:/bin:/usr/bin:/bin:/usr/sbin:/sbin"
	};
	char *find_binary_env_no_path[3] = {
	 "PTH=/Users/adpusel/:/bin:/usr/bin:/bin:/usr/sbin:/sbin"
	};

	find_binary_test("ls", find_binary_env, "/bin/ls", 1);
	find_binary_test("l", find_binary_env, NULL, 2);
	find_binary_test("ls", find_binary_env_no_path, NULL, 3);
	find_binary_test("db_dump", find_binary_env, "/usr/bin/db_dump", 4);

	/* echo test ------------------------------------------------------------ */
	echo_test("toto", "toto\n", 1);
	echo_test("toto supre 'auau  aue' ", "toto supre auau  aue\n", 2);
	echo_test("-n toto supre 'auau  aue' ", "toto supre auau  aue", 3);
	echo_test("-n", "", 4);
	echo_test("\n", "\n", 5);
}

void test_all()
{
	t_ms *a = &m;
	(void) a;

	tested_test();


	g_fd = 0;

	//	while (1)
	//	{
	//		ft_strsplitprint_test(read_command());
	//	}
	/**/
}