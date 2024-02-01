/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:29:33 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/01 18:58:06 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	ft_cmd(t_data *data, char *cmd, char **envp)
{
	int	i;

	i = -1;
	data->commt = ft_split(cmd, ' ');
	while (data->rout[++i])
	{
		data->wanted = ft_strjoin(data->rout[i], data->commt[0]);
		if (access(data->wanted, 0) == 0)
			execve(data->wanted, data->commt, envp);
	}
	ft_error(2);
	exit(1);
}
