/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:29:33 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/05 04:25:13 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_routes(char **envp)
{
	int		i;
	int		k;
	char	*temp;
	char	**rout;

	i = 0;
	k = 0;
	temp = "";
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	rout = ft_split(envp[i], ':');
	temp = ft_strjoin(temp, &rout[0][5]);
	free(rout[0]);
	rout[0] = ft_strdup(temp);
	free(temp);
	while (rout[k])
	{
		temp = ft_strjoin(rout[k], "/");
		if (rout[k])
			free(rout[k]);
		rout[k] = ft_strdup(temp);
		free(temp);
		k++;
	}
	return (rout);
}

int	ft_search(t_data *data, char *search)
{
	int	i;

	i = -1;
	while (data->rout[++i])
	{
		data->wanted = ft_strjoin(data->rout[i], search);
		if (access(data->wanted, 0) == 0)
			return (0);
	}
	return (1);
}
