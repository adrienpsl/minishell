#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#import "libft.h"

# define OPTION_I 1
# define OPTION_U 2

typedef struct s_ms
{
	int i;
	char **env;
	char **env_tmp;
	char *buffer;
	char buffer_array[4097];
} t_ms;

/*
**	structure programme
*/
t_ms m;

/*
**	test global
*/
int g_test_fd;
char g_test_cd_buffer[4000];
char **g_test_env;

// env
void ft_echo(char **argv);
int ft_unsetenv(char *removing_var);
int ms_env_copy(char **env);
int ft_setenv(char **argv);
char *ms_env_get_value(char *key, char **argv);
int ms_env_modify(char *key, char *new_value);
void ft_env(char **argv);
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
char **ms_unset_env(char *removing_var, char **env);
// echo
// env
//
//

// action
int ms_ex_binary(char *path, char **argv, char **env);
int ms_do_cmd(char **argv);
void ms_loop();
// path
char *search_binary_in_path(char *path, char *name);
char *ft_find_binary(char *binary_name);

// test
void test_all();

// utils
void signal_program(int t);

#endif //MINISHELL_MINISHELL_H
