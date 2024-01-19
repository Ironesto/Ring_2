/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:40:35 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/19 06:00:56 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **ft_routes(char **envp)
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
		//ft_printf("%s\n", rout[k]);
	}
	return (rout);
}

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

int	ft_search(t_data *data, char *search)
{
	int	i;

	i = -1;
	while(data->rout[++i])
	{
		data->wanted = ft_strjoin(data->rout[i], search);
		if (access(data->wanted, 0) == 0)
			return (ft_printf("%s\n", data->wanted), 0);
	}
	return (1);
}

void	ft_commands(t_data *data, char **c1, char **c2)
{
	//guardar los comandos y sus opciones
}

void	ft_init(t_data *data, char **envp)
{
	data->rout = ft_routes(envp);
	data->wanted = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int	fd1[2];
	int	fd;
	int	status;
	int	pid;
	
	//if (argc != 5)
		//return (1);
	ft_init(&data, envp);
	fd1[0] = open("input.txt", O_RDONLY);
	//fd1[0] = 0;
	fd1[1] = 1;
	//fd = open("./ouput.txt", O_RDONLY);
	ft_search(&data, "ls");
	pipe(fd1);
	pid = fork();
	if (pid == 0)
	{
		close(fd1[0]);
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[1]);
		execve(data.wanted, argv, envp);
	}
	else
	{
		close(fd1[1]);
		pid = fork();
		if (pid == 0)
		{
			ft_search(&data, "wc");
			fd = open("output.txt", O_WRONLY | O_APPEND);
			dup2(fd1[0], STDIN_FILENO);
			close(fd1[0]);
			dup2(fd, STDOUT_FILENO);
			execve(data.wanted, argv, envp);
		}
		else
		{
			close(fd1[0]);
		}
	}
	wait(&status);
	wait(&status);
	//ft_free(rout);
	return (0);
}