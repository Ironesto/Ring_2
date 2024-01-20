/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:40:35 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/20 05:35:51 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	firstson(t_data *data, int *pip, char **envp)
{
	if (ft_search(data, data->comm1[0]) == 1)
		return (1);
	dup2(data->fdin, STDIN_FILENO);
	dup2(pip[1], STDOUT_FILENO);
	close(pip[0]);
	close(pip[1]);
	execve(data->wanted, data->comm1, envp);
	return (0);
}

void	secondson(t_data *data, int *pip, char **envp)
{
	ft_search(data, data->comm2[0]);
	data->fdout = open(data->outfile, O_WRONLY | O_CREAT);
	dup2(pip[0], STDIN_FILENO);
	close(pip[0]);
	close(pip[1]);
	dup2(data->fdout, STDOUT_FILENO);
	execve(data->wanted, data->comm2, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int	pip[2];
	int	status;
	int	pid;

	atexit(ft_leaks);	//comprobrar leaks
	
	if (argc != 5)
		return (ft_error(0), 1);	//explicacion strerror
	ft_init(&data, envp, argv);
	if (data.fdin < 0)
		return (ft_error(1), ft_allfree(&data), 1); // usar exit?
	pipe(pip);
	pid = fork();
	if (pid == 0)
		firstson(&data, pip, envp); //error de que el hijo no se cree
	pid = fork();
	if (pid == 0)
		secondson(&data, pip, envp); //error de que el hijo no se cree
	wait(&status);
	close(pip[0]);
	close(pip[1]);
	close(data.fdin);
	close(data.fdout);
	ft_allfree(&data);
	return (0);
}
