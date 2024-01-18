/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:40:35 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/18 04:30:50 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **ft_routes(char **envp)
{
	int	i;
	int	k;
	char **rout;

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

static char	**ft_free(char **str)
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

int	main(int argc, char **argv, char **envp)
{
	char **rout;

	if (argc != 5)
		return (1);		//gestionar error?
	rout = ft_routes(envp);
	ft_free(rout);
	return (0);
}