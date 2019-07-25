
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
	new_passed_test();


//	char **t1 = ft_strsplit("$1 ", " ");
//	g_ms.env = ft_strsplit("1=toto", " ");
//
//	replace_jocker(t1);




}