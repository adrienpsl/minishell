#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

# import "libft.h"
# include <dirent.h>
#include <sys/termios.h>

#import "minishell.limit.h"
#import "minishell.error.h"

# define OPTION_I 1
# define OPTION_U 2

# define MS_NAME "mimishell"
# define MS_DEL "\177"
# define MS_TAB "\t"


typedef struct func_name {
	char *name;
	int (*f)(char **arg);
} t_n;

typedef struct minishell {
	int fd;
	int is_test;
	struct termios termios;
	int is_raw;
	char **env;
	int ctrlc;
} t_ms;

t_ms g_ms;


/*
**	canonical
*/
void ms_set_raw();

/*
**	cd
*/
char *ms_test_input_line();
/*
**	env
*/
int ms_copy_env(char **dest, char **src);
int ms_env_remove(char **env, char *var);
char *ms_get_value(char *key);
int ms_exit(char **argv);

// env
int ms_echo(char **argv);
int ms_setenv(char **argv);
//int ms_env_copy(char **env);
char **ms_env(char **argv, char ***real_env);
int ms_func_search_var$name(char *current, void *p_searched);
char *ms_find_binary(char *bin_name, int start_mode);

int ms_test_file(char *builtin, char *path);
void signal_minishell(int sign);
void ms_loop();

char *ms_get_new_line();

int ms_handle_binary(char **argv);

// parse
char **ms_parser();

//env
int ms_setenv(char **argv);
int ms_cd(char **argv);
int ms_unsetenv(char **argv);
char **ms_env_add(char **src, char *var, int do_free);

// test
void test_all(char **env);

// utils
void signal_program(int t);

#endif //MINISHELL_MINISHELL_H
