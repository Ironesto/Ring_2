#include "pipex_bonus.h"

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
