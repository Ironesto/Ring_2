/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:19:50 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/31 19:20:11 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include "./../libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_data
{
	char	**rout;
	char	**commt;
	char	*wanted;
}	t_data;

			//commands.c
char	**ft_routes(char **envp);
int		ft_search(t_data *data, char *search);

			//utils.c
char	**ft_free(char **str);
void	ft_error(int i);
void	ft_allfree(t_data *data);
void	ft_finish(t_data *data, int *pip);

#endif