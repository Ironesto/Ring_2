/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:40:27 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/05 04:25:05 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	char	**comm1;
	char	**comm2;
	char	*wanted;
	char	*infile;
	char	*outfile;
	int		fdin;
	int		fdout;
}	t_data;

			//commands.c
char	**ft_routes(char **envp);
int		ft_search(t_data *data, char *search);

			//utils.c
char	**ft_free(char **str);
void	ft_error(int i);
void	ft_allfree(t_data *data);
void	ft_finish(t_data *data, int *pip);

			//family.c
int		ft_mother(t_data *data, int *pip, char **envp);

#endif