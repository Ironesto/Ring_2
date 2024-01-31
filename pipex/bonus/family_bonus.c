#include "pipex_bonus.h"

static int	firstson(t_data *data, int *pip, char **envp)
{
	if (ft_search(data, data->comm1[0]) == 1)
		return (ft_error(2), 1);
	dup2(data->fdin, STDIN_FILENO);
	dup2(pip[1], STDOUT_FILENO);
	close(pip[0]);
	close(pip[1]);
	execve(data->wanted, data->comm1, envp);
}

static int	midson(t_data *data, char **envp)
{
	int	pip[2];

	pipe(pip);
	if (ft_search(data, data->commt[0]) == 1)
		return (ft_error(2), 1);
	execve(data->wanted, data->commt, envp);
}

static int	secondson(t_data *data, int *pip, char **envp)
{
	if (ft_search(data, data->comm2[0]) == 1)
		return (ft_error(2), 1);
	data->fdout = open(data->outfile, O_WRONLY | O_CREAT);
	dup2(pip[0], STDIN_FILENO);
	close(pip[0]);
	close(pip[1]);
	dup2(data->fdout, STDOUT_FILENO);
	execve(data->wanted, data->comm2, envp);
}

int	ft_mother(t_data *data, int *pip,char **argv, char **envp)
{
	int	pid;
	int	i;
	int	status;

	i = 3;
	pipe(pip);
	pid = fork();
	if (pid == 0)
	{
		firstson(data, pip, envp);
	}
	else if (pid < 0)
		return (1);
	//waitpid(pid, &status, 0);
	while (i < data->pnum)
	{
		//pipe(pip);
		pid = fork();
		if (pid == 0)
		{
			close(pip[0]);
			dup2(pip[1], STDOUT_FILENO);
			data->commt = ft_split(argv[i], ' ');
			midson(data, envp);
		}
		else
		{
			close(pip[1]);
			dup2(pip[0], STDIN_FILENO);
			waitpid(pid, &status, 0);
		}
		i++;
	}
	pid = fork();
	if (pid == 0)
	{
		secondson(data, pip, envp);
	}
	else if (pid < 0)
		return (1);
	waitpid(pid, &status, 0);
	return (0);
}
