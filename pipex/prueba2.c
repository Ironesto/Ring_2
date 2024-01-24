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

int exec(char **argv, char **envp, int i) 
{
    int fd[2];
    int status;
    int has_pipe = argv[i] && !strcmp(argv[i], "|");

    if (has_pipe && pipe(fd) == -1)
        return err("error: fatal\n");

    int pid = fork();
    if (!pid) 
    {
        argv[i] = 0;
        if (has_pipe && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
            return err("error: fatal\n");
        execve(*argv, argv, envp);
        return err("error: cannot execute "), err(*argv), err("\n");
    }

    waitpid(pid, &status, 0);
    if (has_pipe && (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
        return err("error: fatal\n");
    return WIFEXITED(status) && WEXITSTATUS(status);
}

int	main(int argc, char **argv, char **envp)
{
	int	pip[2];
	int	i;
	int	pid;
	int status;
	t_data	data;

        while (argv[i] && argv[++i]) 
        {
            argv += i;
            i = 0;
            while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
                i++;
            if (!strcmp(*argv, "cd"))
                status = cd(argv, i);
            else if (i)
                status = exec(argv, envp, i);
        }
}