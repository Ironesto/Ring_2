/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:40:35 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/31 20:29:16 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_leaks(void)
{
	system("leaks -q pipex");
}

void	ft_init(t_data *data, char **envp)
{
	data->rout = ft_routes(envp);
	data->wanted = NULL;
	data->commt = NULL;
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
	return ;
}

void	son(t_data *data, char *cmd, char **envp)
{
	int	fd[2];
	int	pid;
	int	status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_cmd(data, cmd, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &status, 0);
	}
}

void	ft_temp(char *wtd, int fdin)
{
	char	*str;
	char	*str2;

	str = "";
	write(1,"heredoc> ", 9);
	str2 = get_next_line(0);
	while (ft_strncmp(str2, wtd, ft_strlen(str2) - 1))
	{
		write(1,"heredoc> ", 9);
		str = ft_strjoin(str, str2);
		str2 = get_next_line(0);
	}
	dup2(fdin, STDOUT_FILENO);
	ft_printf("%s", str);
}
int	here_doc(char *str)
{
	int fdin;
	
	fdin = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_temp(str, fdin);
	close(fdin);
	fdin = open(".tmp", O_RDONLY);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return (3);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;
	int		fdin;
	int		fdout;
	
	atexit(ft_leaks);

	fdout = open(argv[argc - 1], O_WRONLY);
	ft_init(&data, envp);
	if (!ft_strncmp(argv[1], "here_doc", 8))
		i = here_doc(argv[2]);
	else
	{
		fdin = open(argv[1], O_RDONLY);
		dup2(fdin, STDIN_FILENO);
		i = 2;
	}
	while (i < argc - 2)
	{
		son(&data, argv[i], envp);
		i++;
	}
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	unlink(".tmp");
	ft_cmd(&data, argv[argc - 2], envp);
	return (0);
}
