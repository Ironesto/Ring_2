#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct s_data
{
	char	**rout;
	char	**commt;
	char	*wanted;
	int		fdin;
	int		fdout;
}	t_data;

char	**ft_routes(char **envp)
{
	int	i;
	int	k;
	char **rout;

	i = 0;
	k = -1;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	rout = ft_split(envp[i], ':');
	rout[0] = &rout[0][5];
	while (rout[++k])
		rout[k] = ft_strjoin(rout[k], "/");
	return (rout);
}

int	ft_search(t_data *data, char **argv, char k)
{
	int	i;

	i = -1;
	data->commt = ft_split(argv[k], ' ');
	while(data->rout[++i])
	{
		data->wanted = ft_strjoin(data->rout[i], data->commt[0]);
		if (access(data->wanted, 0) == 0)
			return (0);
	}
	return (1);
}

void	ft_init(t_data *data, char **envp, int argc, char **argv)
{
	data->rout = ft_routes(envp);
	data->wanted = NULL;
	data->fdin = open(argv[1], O_RDONLY);
	data->fdout = open(argv[argc - 1], O_WRONLY);
}

void	ft_error(int i)
{
	if (i == 0)
		write(2,"ERROR\nWrong number of arguments\n",32);
	if (i == 1)
		write(2, "ERROR\nIncorrect infile\n", 23);
	if ( i == 2)
		write(2, "ERROR\nOrder not found\n", 22);
}

static int	son(t_data *data, int k, char **argv, char **envp)
{
  	if (ft_search(data, argv, k) == 1)
		return(1);
	ft_printf("Borrar esto en son : %s\n", data->commt[0]);
	execve(data->wanted, data->commt, envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int 	pip[2];
	int		pid;
	int		cnum;
	t_data	data;
	int		i;
	int		status;

	i = 3;
	cnum = argc - 3;
	ft_init(&data, envp, argc, argv);
	if (argc - 3 == 1)
	{
		dup2(data.fdin, STDIN_FILENO);
		close(data.fdin);
		dup2(data.fdout, STDOUT_FILENO);
		close(data.fdout);
		son(&data, 2, argv, envp);
		return (0);
	}
	if (pip != 0)
	{	
		dup2(data.fdin, STDIN_FILENO);
		dup2(pip[1], STDOUT_FILENO);
		close(data.fdin);
		close(pip[1]);
		puts("entra");
		son(&data, 2, argv, envp);
	}
	while (i < argc - 1)
	{	
		pipe(pip);
		pid = fork();
		if (pid == 0)
		{
			puts("entra");
			dup2(pip[0], STDIN_FILENO);
			close(pip[0]);
			dup2(pip[1], STDOUT_FILENO);
			son(&data, i, argv, envp);
			close(pip[1]);
			return (0);
		}
		i++;
	}
	wait(&status);
	puts("padre");
	dup2(pip[0], STDIN_FILENO);
	close(pip[0]);
	dup2(data.fdout, STDOUT_FILENO);
	close(data.fdout);
	son(&data, i, argv, envp);
	//ft_printf("\nesta %s\n", argv[argc - 2]);
	return (0);
}
