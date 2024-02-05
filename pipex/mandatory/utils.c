/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:58:33 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/05 04:25:01 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		write(2, "ERROR\nWrong number of arguments\n", 32);
	if (i == 1)
		write(2, "ERROR\nIncorrect infile\n", 23);
	if (i == 2)
		write(2, "ERROR\nOrder not found\n", 22);
	if (i == 3)
		write(2, "ERROR\nFailed creating child\n", 28);
}

void	ft_allfree(t_data *data)
{
	if (data->rout)
		ft_free(data->rout);
	if (data->comm1)
		ft_free(data->comm1);
	if (data->comm2)
		ft_free(data->comm2);
	if (data->infile)
		free(data->infile);
	if (data->outfile)
		free(data->outfile);
	if (data->wanted)
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
