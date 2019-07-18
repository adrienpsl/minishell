#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

# import "libft.h"
# include <dirent.h>

# define OPTION_I 1
# define OPTION_U 2

# define MS_BUFF_MAX 4096
# define MS_NAME "mimishell"

typedef struct s_ms
{
	int i;
	char **env;
	char **argv;
	char **env_tmp;
	char *buffer;
	char buffer_array[4097];
} t_ms;

typedef struct s_test
{
	int fd;
	char buffer[4000];
	int end_test;
} t_ms_test;


/*
**	structure programme
*/
t_ms g_ms;
t_ms_test g_mst;

/*
**	test global
*/

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

int is_quote_paired(char *command);
char *get_all_commands();

// parse
char **build_argv(char *line);
char **read_command();

// builtin
int ft_cd(char **argv);
char *get_env_variable(char *line, int end);
char *replace_env_variable(char *line);
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
