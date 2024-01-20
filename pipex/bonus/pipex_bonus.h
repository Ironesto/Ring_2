#ifndef PIPEX_BONUS_H
# define PIPEX__BONUS_H

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

#endif