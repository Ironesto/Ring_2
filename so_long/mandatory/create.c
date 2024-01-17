/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:27:07 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/09 20:12:25 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_fd(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	seeimage2(t_data *data)
{
	mlx_texture_t	*image;

	if (ft_fd("./assets/gabi.png") >= 0)
		image = mlx_load_png("./assets/gabi.png");
	else
		return (write(2, "Error\nSprite salida cerrada no errónea\n", 40), 1);
	data->image.gabi = mlx_texture_to_image(data->mlx, image);
	mlx_delete_texture(image);
	if (ft_fd("./assets/gabi2.png") >= 0)
		image = mlx_load_png("./assets/gabi2.png");
	else
		return (write(2, "Error\nSprite salida abierta no errónea\n", 40), 1);
	data->image.exit = mlx_texture_to_image(data->mlx, image);
	mlx_delete_texture(image);
	if (ft_fd("./assets/cartucho.png") >= 0)
		image = mlx_load_png("./assets/cartucho.png");
	else
		return (write(2, "Error\nSprite coleccionable erróneo\n", 36), 1);
	data->image.cartucho = mlx_texture_to_image(data->mlx, image);
	mlx_delete_texture(image);
	return (0);
}

int	seeimage(t_data *data)
{
	mlx_texture_t	*image;

	if (ft_fd("./assets/wall.png") >= 0)
		image = mlx_load_png("./assets/wall.png");
	else
		return (write(2, "Error\nSprite pared erróneo\n", 28), 1);
	data->image.wall = mlx_texture_to_image(data->mlx, image);
	mlx_delete_texture(image);
	if (ft_fd("./assets/floor2P.png") >= 0)
		image = mlx_load_png("./assets/floor2P.png");
	else
		return (write(2, "Error\nSprite suelo erróneo\n", 28), 1);
	data->image.floor = mlx_texture_to_image(data->mlx, image);
	mlx_delete_texture(image);
	if (ft_fd("./assets/fermin.png") >= 0)
		image = mlx_load_png("./assets/fermin.png");
	else
		return (write(2, "Error\nSprite personaje erróneo\n", 32), 1);
	data->image.fermin = mlx_texture_to_image(data->mlx, image);
	mlx_delete_texture(image);
	if (seeimage2(data) == 1)
		return (1);
	return (0);
}

void	createmap(t_data *data, int size)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->h)
	{
		x = 0;
		while (x < data->w)
		{
			if (ft_strchr("0CPE", data->map[y][x]))
				mlx_image_to_window(data->mlx,
					data->image.floor, x * size, y * size);
			else if (data->map[y][x] == '1')
				mlx_image_to_window(data->mlx,
					data->image.wall, x * size, y * size);
			x++;
		}
		y++;
	}
}

void	createitem(t_data *data, int size)
{
	int	x;
	int	y;

	y = 0;
	while (y++ < data->h - 1)
	{
		x = 0;
		while (x++ < data->w)
		{
			if (data->map[y][x] == 'C')
				mlx_image_to_window(data->mlx,
					data->image.cartucho, x * size, y * size);
			if (data->map[y][x] == 'E')
			{
				mlx_image_to_window(data->mlx, data->image.exit,
					x * size, y * size);
				data->image.exit->instances[0].enabled = false;
				mlx_image_to_window(data->mlx, data->image.gabi,
					x * size, y * size);
			}
		}
	}
	mlx_image_to_window(data->mlx, data->image.fermin,
		data->pp.x * size, data->pp.y * size);
}
