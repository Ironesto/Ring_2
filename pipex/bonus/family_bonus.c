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
	return (0);
}

static int	midson(t_data *data, int *pip, char **envp)
{
	if (ft_search(data, data->commt[0]) == 1)
		return (ft_error(2), 1);
	dup2(pip[0], STDIN_FILENO);
	close(pip[0]);
	dup2(pip[1], STDOUT_FILENO);
	close(pip[1]);
	execve(data->wanted, data->commt, envp);
	//return (0);
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
	return (0);
}

int	ft_mother(t_data *data, int *pip,char **argv, char **envp)
{
	int	pid;
	int	i;

	i = 3;
	pid = fork();
	if (pid == 0)
	{
		if (firstson(data, pip, envp) == 1)
			return (1);
	}
	else if (pid < 0)
		return (1);
	while (i < data->pnum - 2)
	{
		if (pid == 0)
		{
		data->commt = ft_split(argv[i], ' ');
		pid = fork();
			if (midson(data, pip, envp) == 1)
				return (1);
		}
		else if (pid < 0)
			return (1);
		i++;
	}
	pid = fork();
	if (pid == 0)
	{
		if (secondson(data, pip, envp) == 1)
			return (1);
	}
	else if (pid < 0)
		return (1);
	return (0);
}
