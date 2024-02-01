/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:40:35 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/01 02:53:04 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_leaks()
{
	system("leaks -q pipex");
}

void	ft_init(t_data *data, char **envp)
{
	data->rout = ft_routes(envp);
	data->wanted = NULL;
	data->commt = NULL;
}

void	son(t_data *data, char *cmd, char **envp)
{
	int	fd[2];
	int	pid;
	int	status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_cmd(data, cmd, envp);
	}
	else if (pid < 0)
		ft_error(3);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &status, 0);
	}
}

void	last_son(t_data *data, char *str, char **envp)
{
	int pid;
	int status;
	pid = fork();
	if (pid == 0)
	{
		dup2(data->fdout, STDOUT_FILENO);
 		close(data->fdout);
		ft_cmd(data, str, envp);
	}
	else if (pid < 0)
		ft_error(3);
	else
		waitpid(pid, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;
	
	atexit(ft_leaks);

	ft_init(&data, envp);
	i = ft_enter(argc, argv, &data);
	while (i < argc - 2)
	{
		son(&data, argv[i], envp);
		i++;
	}
	last_son(&data, argv[argc - 2], envp);
	unlink(".tmp");
	return (0);
}
