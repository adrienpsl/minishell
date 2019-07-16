#include <stdio.h>
#include <minishell.h>

void testss(int t)
{
	(void)t;
	ft_printf("\n");
}

char *ms_find_cmd(char **argv)
{
	char *path;

	if (*argv[0] == '/' && !ms_test_file(*argv, "mimishell"))
		path = *argv;
	else
		path = ft_find_binary(*argv);
	return (path);
}

int do_command(char *path, char **argv, char **env)
{
	pid_t pid;

			signal(SIGINT, testss);

	pid = fork();
	if (pid == 0)
	{
		execve(path, argv, env);
	}
	if (pid > 0)
	{
		wait(&pid);
		signal(SIGINT, signal_handler);
	}
	//	if (pid < 0); // TODO : handle errors.
	return (0);
}

void do_builtin(char **argv)
{
	if (ft_streq(*argv, "cd"))
		ft_cd(argv + 1);
	else if (ft_streq(*argv, "exit"))
		exit(EXIT_SUCCESS);
	else if (ft_streq(*argv, "echo"))
		ft_echo(argv + 1);
	else if (ft_streq(*argv, "setenv"))
		ft_setenv(argv + 1);
	else if (ft_streq(*argv, "unsetenv"))
		ft_unsetenv(argv[1]);
}

void signal_handler(int sign)
{
	(void)sign;
	ft_printf("\n$> ");
}


void ms_loop()
{
	char **argv;
	static char *builtin[7] = { "cd", "echo", "setenv", "unsetenv", "env", "exit", NULL };
	char *path;

	ft_printf("$> ");
	while ((argv = read_command()))
	{
//		signal(SIGINT, signal_handler);
		if (*argv == NULL)
			(void) 1; // print truc
		else if (ft_strsplit_search(builtin, ft_strsplit_search_streq, *argv) > -1)
			do_builtin(argv);
		else if ((path = ms_find_cmd(argv)))
			do_command(path, argv, m.env);
		else
			ft_printf("no such binary\n");
		ft_str_split_free(&argv);
		ft_printf("$> ");
	}
}

int main(int ac, char **av, char **env)
{
	if (env == NULL)
		return (EXIT_FAILURE);
	(void) ac;
	(void) av;
	ft_bzero(&m, sizeof(m));
	ms_env_copy(env);
	m.buffer = m.buffer_array;

	signal(SIGINT, signal_handler);
		test_all();
//	ms_loop();

	return (0);
}