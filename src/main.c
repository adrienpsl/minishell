#include <stdio.h>
#include <minishell.h>

void do_command(char *path, char **argv)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		execve(path, argv, m.env);
	if (pid > 0)
		wait(&pid);
	//	if (pid < 0); // TODO : handle errors.
}

void do_builtin(char **argv)
{
	if (ft_streq(*argv, "cd"))
		ft_cd(argv + 1);
	else if (ft_streq(*argv, "exit"))
		exit(EXIT_SUCCESS);
	else if (ft_streq(*argv, "echo"))
		ft_echo(argv + 1);
	else if (ft_streq(*argv, "echo"))
		ft_echo(argv + 1);

}

void ms_loop()
{
	char **argv;
	char *path;
	static char *builtin[7] = { "cd", "echo", "setenv", "unsetenv", "env", "exit", NULL };

	ft_printf("$> ");
	while ((argv = read_command()))
	{
		if (*argv == NULL)
			(void) 1; // print truc
		else if (ft_strsplit_search(builtin, ft_strsplit_search_streq, *argv) > -1)
			do_builtin(argv);
		else if (*argv[0] == '/')
		{
			if (!ms_test_file(*argv, "mimishell"))
				do_command(path, argv);
		}
		else if ((path = ft_find_binary(*argv)))
			do_command(path, argv);
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
	//	test_all();
	ms_loop();

	return (0);
}