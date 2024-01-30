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

void ft_leaks()
{
	system("leaks -q 'pipex'");
}

void	ft_init(t_data *data, char **envp, char **argv)
{
	data->rout = ft_routes(envp);
	data->wanted = NULL;
	data->comm1 = ft_split(argv[2], ' ');	//proteger variables?
	data->comm2 = ft_split(argv[3], ' ');
	data->infile = ft_strdup(argv[1]);
	data->outfile = ft_strdup(argv[4]);
	data->fdin = open(data->infile, O_RDONLY);
}

char	**ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free (str);
	return (NULL);
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

void	ft_allfree(t_data *data)
{
	ft_free(data->rout);
	ft_free(data->comm1);
	ft_free(data->comm2);
	free(data->infile);
	free(data->outfile);
	free(data->wanted);
}

void	ft_finish(t_data *data, int *pip)
{
	close(pip[0]);
	close(pip[1]);
	close(data->fdin);
	close(data->fdout);
	ft_allfree(data);
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