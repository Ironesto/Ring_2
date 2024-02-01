/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:59:41 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/01 18:59:41 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	firstson(t_data *data, int *pip, char **envp)
{
	if (ft_search(data, data->comm1[0]) == 1)
		return (ft_error(2), ft_finish(data, pip), 1);
	dup2(data->fdin, STDIN_FILENO);
	dup2(pip[1], STDOUT_FILENO);
	close(pip[0]);
	close(pip[1]);
	execve(data->wanted, data->comm1, envp);
	return (0);
}

static int	secondson(t_data *data, int *pip, char **envp)
{
	if (ft_search(data, data->comm2[0]) == 1)
		return (ft_error(2), ft_finish(data, pip), 1);
	data->fdout = open(data->outfile, O_WRONLY | O_CREAT, 0777);
	dup2(pip[0], STDIN_FILENO);
	close(pip[0]);
	close(pip[1]);
	dup2(data->fdout, STDOUT_FILENO);
	execve(data->wanted, data->comm2, envp);
	return (0);
}

int	ft_mother(t_data *data, int *pip, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (firstson(data, pip, envp) == 1)
			return (1);
	}
	else if (pid < 0)
		return (ft_error(3), 1);
	pid = fork();
	if (pid == 0)
	{
		if (secondson(data, pip, envp) == 1)
			return (1);
	}
	else if (pid < 0)
		return (ft_error(3), 1);
	return (0);
}
