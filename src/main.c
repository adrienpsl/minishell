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

void do_command(char *path, char **argv)
{
	int father;

	father = fork();
	if (father > 0)
	{
		wait(NULL);
		printf("done====================================================================== \n");
	}
	if (father == 0)
	{
		execve(path, argv, m.env);
		perror("last one");
	}
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

void ms_loop()
{
	char **argv;
	char *path;

	// while no exit in first argument

	while ((argv = read_command()))
	{
		// if commands start with / > find path
		//
		path = ft_find_binary(*argv);
		if (!path)
			ft_printf("no such binary\n");
		else
			do_command(path, argv);
	}
}

int main(int ac, char **av, char **env)
{
	if (env == NULL)
		return EXIT_FAILURE;

	(void) ac;
	(void) av;
	ft_bzero(&m, sizeof(m));
	ms_env_copy(env);
	m.buffer = m.buffer_array;

		test_all();


//	ms_loop();
	//	char *toto[2] = { "/" };
	//	pid_t father;
	//	(void)father;
	//
	//	while(1)
	//	{
	//		father = fork();
	//		if (father > 0)
	//		{
	//			wait(NULL);
	//			printf("father \n");
	//		}
	//		if (father == 0)
	//		{
	//			printf("processs \n");
	//			execve("/bin/ls", toto, NULL);
	//		}
	//	}
	return 0;
}