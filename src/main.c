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

	pid = fork();
	if (pid == 0)
		execve(path, argv, m.env);
	if (pid > 0)
		wait(&pid);
	if (pid < 0)
		; // TODO : handle errors.
}

void do_builtin(char **argv)
{
	if (ft_str_split_count(argv) == 0)
		return;
	else if (ft_streq(*argv, "cd"))
		ft_cd(argv + 1);
	//	else if (ft_streq(*argv, "echo"))
	//		ft_echo()
}

// funtion search in split.


void ms_loop()
{
	char **argv;
	char *path;

	// while no exit in first argument

	while ((argv = read_command()))
	{
		// if is in split >

		// if start / > test file exist

		// else find binary
		if ((path = ft_find_binary(*argv)))
			do_command(path, argv);
		// do command

		// or print error.
		else
			ft_printf("no such binary\n");
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