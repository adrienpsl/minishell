#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

# import "libft.h"
# include <dirent.h>

# define OPTION_I 1
# define OPTION_U 2


# define MS_NAME "mimishell"

/*
**	define Max Var
*/
#define MS_MAX_ARG 40000

# define MS_MAX_ENV_SIZE 100
# define MS_MAX_ENV_SIZE_STR "100"

# define MS_BUFFER_SIZE 4095
# define MS_BUFFER_SIZE_STR "4095"

# define MS_VAR_SIZE_MAX 1023
# define MS_VAR_SIZE_MAX_STR "1023"

typedef struct s_ms
{
	int i;
	int is_env;
	char **env;
	char *tmp_env[MS_MAX_ENV_SIZE + 1];
	char *tmp_buffer[4095 + 1];
	char **argv;
	char *arg[40000];
	char **env_tmp;
	char buffer[MS_BUFFER_SIZE + 1];
} t_ms;

typedef struct s_test
{
	int fd;
	char buffer[MS_BUFFER_SIZE + 1];
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

// env
void ft_echo(char **argv);
int ft_unsetenv(char *removing_var);
int ms_env_copy(char **env);
int ft_setenv(char **env);
char *ms_env_get_value(char *key, char **argv);
int ms_env_modify(char *key, char *new_value);
int ft_env(char ***argv);
int ms_search_function(char *current, void *p_searched);

int ms_test_file(char *path, char *builtin);
void signal_minishell(int sign);

char *ms_parser_get_commands();

// parse
char **ms_parser_read_command();

// builtin
int ft_cd(char **argv);
int ms_unset_env(char *removing_var, char **env, char ***out);
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

#endif //MINISHELL_MINISHELL_H
