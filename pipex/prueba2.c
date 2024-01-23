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
	{
		rout[k] = ft_strjoin(rout[k], "/");
		//ft_printf("ruta: %s\n",rout[k]);
	}
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
	//ft_printf("fdin: %d de %s\n", data->fdin, argv[1]);
	data->fdout = open(argv[argc - 1], O_WRONLY);
	//ft_printf("fdout: %d de %s\n", data->fdout, argv[argc - 1]);
}

static int	son(t_data *data, int k, char **argv, char **envp)
{
  	if (ft_search(data, argv, k) == 1)
		return(1);
	//ft_printf("Borrar esto en son : %s\n", data->commt[0]);
	execve(data->wanted, data->commt, envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	pip[10][2];
	int	i;
	int	pid[10];
	t_data	data;

	i = 2;
	ft_init(&data, envp, argc, argv);
	pipe(pip[0]);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		dup2(data.fdin, 0);
		dup2(pip[0][1], 1);
		close(pip[0][0]);
		close(pip[0][1]);
		son(&data, i, argv, envp);
	}
/* 	while (i < argc - 2)
	{ */
		pipe(pip[1]);
		pid[1] = fork();
		if (pid[1] == 0)
		{
			dup2(pip[0][0], 0);
			dup2(pip[1][1], 1);
			close(pip[1][0]);
			close(pip[1][1]);
			close(pip[0][1]);
			close(pip[0][0]);
			son(&data, 3, argv, envp);
		}
		i++;
/* 	} */
	//pipe(pip);
	pid[2] = fork();
	if (pid[2] == 0)
	{
	//pipe(pip);
	dup2(pip[1][0], 0);
	dup2(data.fdout, 1);
	close(pip[1][0]);
	close(pip[1][1]);
	son(&data, 4, argv, envp);
	}
}