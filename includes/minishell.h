#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

# import "libft.h"
# include <dirent.h>

#import "minishell.limit.h"
#import "minishell.error.h"

# define OPTION_I 1
# define OPTION_U 2

# define MS_NAME "mimishell"




int g_fd;
char **g_env;
char **g_tmp_env;

/*
**	cd
*/

/*
**	env
*/
int ms_copy_env(char **dest, char **src);
int ms_env_remove(char **env, char *var);
char *ms_get_value(char *key);


// env
void ft_echo(char **argv);
int ms_setenv(char **argv);
int ms_env_copy(char **env);
int ft_setenv(char **env);
int ms_env_get_value(char *key, char *buffer);
int ms_env_modify(char *key, char *new_value);
char **ms_env(char **argv, char ***real_env);
int ms_func_search_var$name(char *current, void *p_searched);
char *ms_find_binary(char *bin_name);

int ms_test_file(char *builtin, char *path);
void signal_minishell(int sign);

char *ms_parser_get_commands();

int ms_handle_binary(char **argv);

// parse
int ms_parser(char ***out);
int replace_jocker(char **argv);

// builtin

//env
int ms_setenv(char **argv);
int ms_cd(char **argv);
int ms_unsetenv(char **argv, char **env);
int ms_env_add(char ***env, char *var);
// echo
// env
//
//

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
int ms_put_in_buffer(char *buffer, char *str);

// init and free

#endif //MINISHELL_MINISHELL_H
