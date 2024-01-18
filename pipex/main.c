/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:40:35 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/18 05:49:01 by gpaez-ga         ###   ########.fr       */
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
		rout[k] = ft_strjoin(rout[k], "/");
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

int	main(int argc, char **argv, char **envp)
{
	char **rout;
	int	fd1[2];
	int	fd;
	int	status;
	int	pid;
	
	fd1[0] = 0;
	//fd1[0] = open("./input.txt", O_RDONLY);
	fd1[1] = 1;
	fd = open("./ouput.txt", O_RDONLY);
	//if (argc != 5)
		//return (1);		//gestionar error?
	pipe(fd1);
	pid = fork();
	if (pid == 0)
	{
		close(fd1[0]);
		dup2(fd1[1], STDOUT_FILENO);
		//ft_printf("%s", get_next_line(fd1[0]));
		close(fd1[1]);
		execl("bin/ls", "ls", "-l", NULL);
	}
	else
	{
		close(fd1[1]);
		pid = fork();
		if (pid == 0)
		{
			fd = open("./ouput.txt", O_RDONLY);
			dup2(fd1[0], STDIN_FILENO);
			dup2(fd, STDOUT_FILENO);
			close (fd1[0]);
			execlp("usr/bin/wc", "wc", NULL);
		}
		else
		{
			close(fd1[0]);
		}
	}
	wait(&status);
	wait(&status);
	rout = ft_routes(envp);
	ft_free(rout);
	return (0);
}