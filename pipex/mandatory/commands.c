/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:29:33 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/31 20:40:46 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_routes(char **envp)
{
	int	i;
	int	k;
	char **temp;
	char **rout;

	i = 0;
	k = -1;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	temp = ft_split(envp[i], ':');
	i = 0;
	temp[0] = &temp[0][5];
	while(temp[i])
		i++;
	rout = malloc(sizeof(char *) * (i + 1));	//falla malloc
	while (temp[++k])
	{
		rout[k] = ft_strjoin(temp[k], "/");
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