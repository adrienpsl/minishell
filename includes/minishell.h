#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

# import "libft.h"
# include <dirent.h>

#import "minishell.limit.h"
#import "minishell.error.h"

# define OPTION_I 1
# define OPTION_U 2

# define MS_NAME "mimishell"


typedef struct s_ms_buffer
{
	char env_tmp[(MS_SIZE_MAX_ENV + 1) * sizeof(char **)];
	char env[(MS_SIZE_MAX_ENV + 1) * sizeof(char **)];
	char argv[(40000) * sizeof(char **)];
	char buffer[MS_SIZE_BUFFER + 1];
	char buffer_tmp[MS_SIZE_BUFFER + 1];
} t_ms_buffer;


typedef struct s_ms
{
	int i;

	int is_env;
	int env_size;

	char **env;
	char **env_tmp;

	char **argv;
	int argv_size;

	char buffer[MS_SIZE_BUFFER + 1];
	char tmp_buffer[MS_SIZE_BUFFER + 1];
	t_ms_buffer data;
} t_ms;

typedef struct s_test
{
	int fd;
	char buffer[MS_SIZE_BUFFER + 1];
} t_ms_test;

/*
**	structure programme
*/
t_ms g_ms;
t_ms_test g_mst;

/*
**	test global
*/

void ms_clear_buffer();
char **g_test_env;

/*
**	env
*/
int ms_copy_env(char **dest, char **src);
int ms_env_remove(char **env, char *var);

// env
void ft_echo(char **argv);
int ft_unsetenv(char *removing_var);
int ms_env_copy(char **env);
int ft_setenv(char **env);
char *ms_env_get_value(char *key, char **argv);
int ms_env_modify(char *key, char *new_value);
int ft_env();
int ms_func_search_var$name(char *current, void *p_searched);

int ms_test_file(char *path, char *builtin);
void signal_minishell(int sign);

char *ms_parser_get_commands();

// parse
char **ms_parser_read_command();

// builtin
int ft_cd(char **argv);
int ms_unset_env(char *removing_var, char **env, char ***out);
int ms_env_remove(char **env, char *var);
int ms_env_add(char **env, char *var);
// echo
// env
//
//

// binary
int ms_handle_binary(char **argv);

// action
int ms_do_cmd(char **argv);
void ms_loop();
// path
//char *ms_search_in_directory(char *directory_path, char *binary_name);

// test
void test_all(char **env);
void init(char **env);

// utils
void signal_program(int t);


// init and free
void ms_free(char **env);
int ms_init(char **env);

#endif //MINISHELL_MINISHELL_H
