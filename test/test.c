
#include <minishell.h>
#include "test.h"
#include "../src/ms.parser.c"

// utils
void test_free(t_split *split);
void test_do_split(ms_test *test, t_split *split);
void ms_passed_test();
void test_set_fd(char *str);
void test_ms_cd(ms_test test);

void new_test_all()
{
	g_test = 1;
	g_ms.is_test = 1;


	ms_passed_test();
}

