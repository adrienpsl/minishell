#include <stdio.h>
#include <minishell.h>

// copie et parse evn

// I need to copy that all stuff inside my
// I will make a wrapper to create and free the env split
// how I will save the useful command inside my env : path and home
//


// utiliser execve
// cette command va dans le
// donc je vais utiliser fork pour faire le travail mon gars

void sig_handler(int sign)
{
	(void) sign;
	ft_printf("\n<$ : ");
}

void do_command(char *path, char **argv)
{
	pid_t pid;
	int res;

	pid = fork();
	if (pid == 0)
	{
		res = execve(path, argv, m.env);
	}
	if (pid > 0)
		wait(&pid);
	//	if (pid < 0); // TODO : handle errors.
}

void do_builtin(char **argv)
{
	if (ft_streq(*argv, "cd"))
		ft_cd(argv + 1);
	if (ft_streq(*argv, "exit"))
		exit(EXIT_SUCCESS);
	//	else if (ft_streq(*argv, "echo"))
	//		ft_echo()
}

int test_file(char *path, char *builtin)
{
	// test existance and right
	if (access(path, F_OK))
	{
		ft_printf("%s: no such file or directory: %s\n", builtin, path);
		return (-1);
	}
	if (access(path, R_OK))
	{
		ft_printf("%s: permission denied: %s\n", builtin, path);
		return (-1);
	}
	if (access(path, X_OK))
	{
		ft_printf("%s: execution denied: %s\n", builtin, path);
		return (-1);
	}
	return (0);
}

void ms_loop()
{
	char **argv;
	char *path;
	static char *builtin[7] = { "cd", "echo", "setenv", "unsetenv", "env", "exit", NULL };

	// while no exit in first argument

	while ((argv = read_command()))
	{
		if (*argv == NULL)
			(void) 1; // print truc
		else if (ft_strsplit_search(builtin, ft_strsplit_search_streq, *argv) > -1)
			do_builtin(argv);
		else if (*argv[0] == '/')
		{
			if (!test_file(*argv, "mimishell"))
				do_command(path, argv);
		}
		else if ((path = ft_find_binary(*argv)))
			do_command(path, argv);
		else
			ft_printf("no such binary\n");
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

	signal(SIGINT, sig_handler);
//	test_all();
	ms_loop();

	return 0;
}