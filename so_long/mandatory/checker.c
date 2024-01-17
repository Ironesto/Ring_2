/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:10:04 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/11 18:19:47 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	finishmapper(t_data *data, char *str, int i)
{
	int	fd;
	int	k;

	k = 0;
	fd = open(str, O_RDONLY);
	while (k < i)
	{
		data->map[k] = get_next_line(fd);
		data->cpy[k] = ft_strdup(data->map[k]);
		k++;
	}
	data->map[k] = NULL;
	data->cpy[k] = NULL;
	free(str);
	close(fd);
}

int	mapper(char *argv, t_data *data)
{
	int		fd;
	int		i;
	char	*str;
	char	*line;

	str = ft_strjoin("./maps/", argv);
	i = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1 || ft_strncmp(&str[ft_strlen(str) - 4], ".ber", 4)
		|| ft_strlen(argv) <= 4)
		return (close(fd), free(str), write(2, ERROR, ft_strlen(ERROR)), 1);
	line = get_next_line(fd);
	if (!line)
		return (free (str), close(fd), write(2, "Error\nLínea vacía\n", 20), 1);
	while (line != NULL)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	data->map = malloc(sizeof(char *) * (i + 1));
	data->cpy = malloc(sizeof(char *) * (i + 1));
	finishmapper(data, str, i);
	return (0);
}

int	comp_path(t_data *data, int y, int x)
{
	if (ft_strchr("0CE", data->cpy[y][x]))
		data->cpy[y][x] = '2';
	if (ft_strchr("0CE", data->cpy[y - 1][x]) && y - 1 >= 0)
		comp_path(data, y - 1, x);
	if (ft_strchr("0CE", data->cpy[y + 1][x]) && y + 1 < data->h - 1)
		comp_path(data, y + 1, x);
	if (ft_strchr("0CE", data->cpy[y][x - 1]) && x - 1 >= 0)
		comp_path(data, y, x - 1);
	if (ft_strchr("0CE", data->cpy[y][x + 1]) && x + 1 < data->w - 1)
		comp_path(data, y, x + 1);
	if (data->cpy[data->ep.y][data->ep.x] == '2')
		return (0);
	return (1);
}

int	ft_checker(char *argv, t_data *data)
{
	if (mapper(argv, data) == 1)
		return (1);
	if (comp_rect(data) == 1)
		return (1);
	if (comp_close(data) == 1)
		return (write(2, "Error\nMapa no cerrado\n", 22), 1);
	if (comp_line(data) == 1)
		return (write(2, "Error\nElemento erróneo\n", 25), 1);
	if (comp_item(data) == 1)
		return (1);
	if (comp_path(data, data->pp.y, data->pp.x) == 1)
		return (write(2, "Error\nSin ruta válida\n", 23), 1);
	return (0);
}
