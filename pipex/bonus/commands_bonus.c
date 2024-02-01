/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:29:33 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/01 02:54:42 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**ft_routes(char **envp)
{
	int		i;
	int		k;
	char	**rout;

	i = 0;
	k = -1;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	rout = ft_split(envp[i], ':');
	rout[0] = &rout[0][5];
	while (rout[++k])
		rout[k] = ft_strjoin(rout[k], "/");
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
	exit(1) ;
}
