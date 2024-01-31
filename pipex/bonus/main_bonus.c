/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:40:35 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/31 02:59:56 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void ft_leaks()
{
	system("leaks -q 'pipex'");
}

void	ft_init(t_data *data, char **envp, char **argv)
{
	data->rout = ft_routes(envp);
	data->wanted = NULL;
	data->commt = NULL;
}

void	ft_cmd(t_data *data, char *cmd, char **envp)
{
	int	i;

	i = -1;
	data->commt = ft_split(cmd, ' ');
	while(data->rout[++i])
	{
		data->wanted = ft_strjoin(data->rout[i], data->commt[0]);
		if (access(data->wanted, 0) == 0)
			execve(data->wanted, data->commt, envp);		
	}
	return ;
}


void son(t_data *data, char *cmd, char **envp)
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
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &status, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;
	int		fdin;
	int		fdout;

	fdin = open(argv[1], O_RDONLY);
	fdout = open(argv[argc - 1], O_WRONLY);
	i = 2;
	ft_init(&data, envp, argv);
	dup2(fdin, STDIN_FILENO);
	while (i < argc - 2)
	{
		son(&data, argv[i], envp);
		i++;
	}
	dup2(fdout, STDOUT_FILENO);
	ft_cmd(&data, argv[argc - 2], envp);
}
