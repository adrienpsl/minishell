#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#import "libft.h"

/*
* * ft_errno_set error
*/
enum ms_error
{
	NO_ENV = 100,
	BAD_VAR,
	BAD_DELETING_KEY,
	STR_NOT_IN_PATH,
	OLDPATH_HAS_BE_DELETED,
	HOME_HAS_BE_DELETED,
	INVALID_PATH,
};

typedef struct s_ms
{
	int i;
	int is_fork;
	int is_text;
	char **env;
	char *buffer;
	char buffer_array[4097];
} t_ms;

/*
**	global
*/
int g_errno;
int g_fd;
char g_test_cd_buffer[4000];
t_ms m;

// env
void ft_echo(char **argv);
int ft_unsetenv(char *removing_var);
int ms_env_copy(char **env);
int ft_setenv(char **argv);
char *ms_env_get_value(char *key);
int ms_env_modify(char *key, char *new_value);
void ft_env();
int ms_search_function(char *current, void *p_searched);

int test_file(char *path, char *builtin);

int is_quote_paired(char *command);
char *get_all_commands();

// parse
char **build_argv(char *line);
char **read_command();

// builtin
int ft_cd(char **argv);
char *get_env_variable(char *line, int end);
char *replace_env_variable(char *line);
// echo
// env
//
//

// path
char *display_dir_content(char *path, char *searched_str);
char *search_binary_in_path(char *path, char *name);
char *ft_find_binary(char *binary_name);

// test
void test_all();

#endif //MINISHELL_MINISHELL_H
