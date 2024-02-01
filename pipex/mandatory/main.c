/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:40:35 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/01 03:01:39 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_leaks()
{
	system("leaks -q pipex");
}

void	ft_init(t_data *data, char **envp, char **argv)
{
	data->rout = ft_routes(envp);
	data->wanted = NULL;
	data->comm1 = ft_split(argv[2], ' ');
	data->comm2 = ft_split(argv[3], ' ');
	data->infile = ft_strdup(argv[1]);
	data->outfile = ft_strdup(argv[4]);
	data->fdin = open(data->infile, O_RDONLY);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int	pip[2];
	int	status;

	atexit(ft_leaks);	//comprobrar leaks
	
	if (argc != 5)
		return (ft_error(0), 1);
	ft_init(&data, envp, argv);
	if (data.fdin < 0)
		return (ft_error(1), ft_allfree(&data), 1);
	pipe(pip);
	ft_mother(&data, pip, envp);
	wait(&status);
	ft_finish(&data, pip);
	return (0);
}
