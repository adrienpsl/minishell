
#include <minishell.h>
#include "test.h"
#include "../src/ms.parser.c"

// utils
void test_free(t_split *split);
void test_do_split(ms_test *test, t_split *split);
void new_passed_test();
void test_set_fd(char *str);
void test_ms_cd(ms_test test);

void test_ms_replace_expansion(ms_test test)
{
	// init
	t_split tSplit;

	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	*ms_get_ptr_env() = ft_strsplit_copy(tSplit.env, 0);


	// function tested
//	char *tmp_expansion_line = ft_strdup(test.expansion_line);
//	char *new_line = ms_replace_expansion(tmp_expansion_line);


	// print error
//	if (
//	 !ft_test_streq(test.new_expansion_line, new_line)
//	 )
//	{
//		printf("ms env %d *******************************\n", test.nb_test);
//		ft_test_if_streq(test.new_expansion_line, new_line, "expansion line");
//	}
//
//	// free
//	ft_strsplit_free(&ms_get_env());
//	ft_str_free(&new_line);
	test_free(&tSplit);
}

void new_test_all()
{
	g_test = 1;
	g_ms.is_test = 1;

	// test is with no value
	test_ms_replace_expansion((ms_test){
		.nb_test = 63,
		.expansion_line = "",
		.new_expansion_line = "",
		.env = ""
	});

	// test with ~ at start
	test_ms_replace_expansion((ms_test){
	 .nb_test = 64,
	 .expansion_line = "~",
	 .new_expansion_line = "toto",
	 .env = "HOME=toto"
	});

	// test with ~ at middle
	test_ms_replace_expansion((ms_test){
	 .nb_test = 65,
	 .expansion_line = "titi ~ tata",
	 .new_expansion_line = "titi toto tata",
	 .env = "HOME=toto SUPER=hola"
	});

	// test with ~ at the end
	test_ms_replace_expansion((ms_test){
	 .nb_test = 66,
	 .expansion_line = "titi tata ~",
	 .new_expansion_line = "titi tata toto",
	 .env = "HOME=toto SUPER=hola"
	});

	// test with ~ and no home
	test_ms_replace_expansion((ms_test){
	 .nb_test = 67,
	 .expansion_line = "titi tata ~",
	 .new_expansion_line = "titi tata ",
	 .env = "SUPER=hola"
	});

	// test with ~ and no home
	test_ms_replace_expansion((ms_test){
	 .nb_test = 68,
	 .expansion_line = "~ titi tata ~",
	 .new_expansion_line = " titi tata ",
	 .env = "SUPER=hola"
	});

	// test with ~ and no home
	test_ms_replace_expansion((ms_test){
	 .nb_test = 69,
	 .expansion_line = "~ ~ ~ ~ ~ ~ ~ ~ ~~ ~ ~ ~ ~ ~ ~ ~",
	 .new_expansion_line = "               ",
	 .env = "SUPER=hola"
	});

	// test with ~ and home
	test_ms_replace_expansion((ms_test){
	 .nb_test = 70,
	 .expansion_line = "~ ~ ~ ~ ~ ~ ~ ~ ~~ ~ ~ ~ ~ ~ ~ ~",
	 .new_expansion_line = "TOTO TOTO TOTO TOTO TOTO TOTO TOTO TOTO TOTOTOTO TOTO TOTO TOTO TOTO TOTO TOTO TOTO",
	 .env = "HOME=TOTO SUPER=hola"
	});

	// test with ~ and home
	test_ms_replace_expansion((ms_test){
	 .nb_test = 70,
	 .expansion_line = "~/desktop",
	 .new_expansion_line = "adpusel/toto/desktop",
	 .env = "HOME=adpusel/toto SUPER=hola"
	});


	// test with $
	test_ms_replace_expansion((ms_test){
	 .nb_test = 71,
	 .expansion_line = "$",
	 .new_expansion_line = "",
	 .env = "SUPER=hola"
	});

	// test with $
	test_ms_replace_expansion((ms_test){
	 .nb_test = 72,
	 .expansion_line = "$super",
	 .new_expansion_line = "hola",
	 .env = "super=hola"
	});

	// test with $
	test_ms_replace_expansion((ms_test){
	 .nb_test = 73,
	 .expansion_line = "tata $super toto",
	 .new_expansion_line = "tata hola toto",
	 .env = "super=hola"
	});

	// test with $
	test_ms_replace_expansion((ms_test){
	 .nb_test = 74,
	 .expansion_line = "tata toto $super",
	 .new_expansion_line = "tata toto hola",
	 .env = "super=hola"
	});

	// test with $
	test_ms_replace_expansion((ms_test){
	 .nb_test = 75,
	 .expansion_line = "tata toto $super",
	 .new_expansion_line = "tata toto hola",
	 .env = "super=hola"
	});

	test_ms_replace_expansion((ms_test){
	 .nb_test = 76,
	 .expansion_line = "tata toto $~super",
	 .new_expansion_line = "tata toto hola",
	 .env = "~super=hola"
	});

	test_ms_replace_expansion((ms_test){
	 .nb_test = 77,
	 .expansion_line = "tata toto ~$~super",
	 .new_expansion_line = "tata toto tata/hola",
	 .env = "~super=hola HOME=tata/"
	});

}

