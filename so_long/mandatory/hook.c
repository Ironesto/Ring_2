/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:14:46 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/09 19:33:03 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	erase_coll(t_data *data)
{
	int	i;

	i = 0;
	while (data->pp.y != data->cp[i].y || data->pp.x != data->cp[i].x)
		i++;
	if (i > data->totcol)
	{
		write(2, "Error\n", 6);
		return ;
	}
	data->image.cartucho->instances[i].enabled = false;
	data->totcol--;
	data->map[data->pp.y][data->pp.x] = '0';
}

static void	opendoor(t_data *data)
{
	data->image.gabi[0].enabled = false;
	data->image.exit->instances[0].enabled = true;
	data->totcol = 0;
	if (data->totcol == 0 && data->map[data->pp.y][data->pp.x] == 'E')
		mlx_close_window(data->mlx);
}

void	hook(void *param)
{
	t_data	*data;
	int		x;
	int		y;

	data = param;
	x = data->image.fermin->instances[0].x;
	y = data->image.fermin->instances[0].y;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) && !compmovy(x, y, 64, data))
		data->image.fermin->instances[0].y -= 2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) && !compmovy2(x, y, 64, data))
		data->image.fermin->instances[0].y += 2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) && !compmovx(y, x, 64, data))
		data->image.fermin->instances[0].x -= 2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D) && !compmovx2(y, x, 64, data))
		data->image.fermin->instances[0].x += 2;
	if (data->map[data->pp.y][data->pp.x] == 'C')
		erase_coll(data);
	if (data->totcol == 1 || data->totcol == 0)
		opendoor(data);
}
