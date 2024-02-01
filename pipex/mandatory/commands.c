/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:29:33 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/01 00:04:23 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_routes(char **envp)
{
	int	i;
	int	k;
	char *temp;
	char **rout;

	i = 0;
	k = -1;
	temp = "";
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	rout = ft_split(envp[i], ':');
	rout[0] = &rout[0][5];
	while (rout[++k])
	{
		temp = ft_strjoin(rout[k], "/");
		//free(rout[k]);
		rout[k] = ft_strdup(temp);
		free(temp);
	}
	return (rout);
}

int	ft_search(t_data *data, char *search)
{
	int	i;

	i = -1;
	while(data->rout[++i])
	{
		data->wanted = ft_strjoin(data->rout[i], search);
		if (access(data->wanted, 0) == 0)
			return (0);
	}
	return (1);
}