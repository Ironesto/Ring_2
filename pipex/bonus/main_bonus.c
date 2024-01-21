/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:40:35 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/21 05:43:03 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void ft_leaks()
{
	system("leaks -q 'pipex'");
}

void	ft_init(t_data *data, char **envp, int argc, char **argv)
{
	data->rout = ft_routes(envp);
	data->wanted = NULL;
	data->comm1 = ft_split(argv[2], ' ');	//proteger variables?
	data->comm2 = ft_split(argv[argc - 2], ' ');
	data->infile = ft_strdup(argv[1]);
	data->outfile = ft_strdup(argv[argc - 1]);
	data->fdin = open(data->infile, O_RDONLY);
	data->pnum = argc - 5;
}

/* void	ft_compcomm_bonus(int argc, char **argv, t_data *data)
{
	int		i;
	char	**temp;
							sin terminar
	i = 1;
	temp = NULL;
	while (++i < argc - 1)

} */

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int	pip[2];
	int	status;

	//atexit(ft_leaks);	//comprobrar leaks

	ft_init(&data, envp, argc, argv);
	if (data.fdin < 0)
		return (ft_error(1), ft_allfree(&data), 1); // usar exit?
	pipe(pip);
	ft_mother(&data, pip, argv, envp);
	wait(&status);
	ft_finish(&data, pip);
	return (0);
}
