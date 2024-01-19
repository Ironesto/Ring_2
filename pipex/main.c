/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:40:35 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/19 18:41:50 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_free(char **str)
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

void	ft_init(t_data *data, char **envp, char **argv)
{
	data->rout = ft_routes(envp);
	data->wanted = NULL;
	data->comm1 = ft_split(argv[2], ' ');
	data->comm2 = ft_split(argv[3], ' ');
	//ft_printf("%s y %s\n", data->comm1[0], data->comm1[1]);
	//ft_printf("%s y %s\n", data->comm2[0], data->comm2[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int	fd1[2];
	int	fd;
	int	status;
	int	pid;
	
	if (argc != 5)
		return (1);
	ft_init(&data, envp, argv);
	fd1[0] = open(argv[1], O_RDONLY);
	//fd1[0] = 0;
	fd1[1] = 1;
	ft_search(&data, data.comm1[0]);
	pipe(fd1);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[0]);
		close(fd1[1]);
		execve(data.wanted, data.comm1, envp);
	}
	close(fd1[1]);
	pid = fork();
	if (pid == 0)
	{
		ft_search(&data, data.comm2[0]);
		fd = open(argv[4], O_WRONLY | O_APPEND);
		dup2(fd1[0], STDIN_FILENO);
		close(fd1[0]);
		dup2(fd, STDOUT_FILENO);
		execve(data.wanted, data.comm2, envp);
	}
	else
	{
		close(fd1[0]);
	}
	wait(&status);
	wait(&status);
	ft_free(data.rout);
	return (0);
}
