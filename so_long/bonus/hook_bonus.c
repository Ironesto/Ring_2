/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:26:40 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/09 20:35:25 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	erase_coll(t_data *data)
{
	int	i;

	i = 0;
	while (data->pp.y != data->cp[i].y || data->pp.x != data->cp[i].x)
		i++;
	if (i > data->totcol + 1)
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

void	hookmov_bonus(t_data *data, int x, int y)
{
	data->image.fermin->instances[0].y += y;
	data->image.fermin2->instances[0].y += y;
	data->image.fermin2->instances[0].x += x;
	data->image.fermin->instances[0].x += x;
}

void	movene_bonus(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < data->image.ale->count)
	{
		x = data->image.ale2->instances[i].x;
		y = data->image.ale2->instances[i].y;
		if (compmovx2e_bonus(y, x, data, i) == 0 && data->ap[i].pos == 0)
			data->image.ale2->instances[i].x++;
		else if (compmovxe_bonus(y, x, data, i) == 0 && data->ap[i].pos == 1)
			data->image.ale2->instances[i].x--;
		else if (compmovy2e_bonus(y, x, data, i) == 0 && data->ap[i].pos == 2)
			data->image.ale2->instances[i].y++;
		else if (compmovye_bonus(y, x, data, i) == 0 && data->ap[i].pos == 3)
			data->image.ale2->instances[i].y--;
		else
			data->ap[i].pos = rand() % 100;
		enemcoll_bonus(data, i);
		movanimene_bonus(data, x, y, i);
		i++;
	}
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
		hookmov_bonus(data, 0, -2);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) && !compmovy2(x, y, 64, data))
		hookmov_bonus(data, 0, 2);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) && !compmovx(y, x, 64, data))
		hookmov_bonus(data, -2, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D) && !compmovx2(y, x, 64, data))
		hookmov_bonus(data, 2, 0);
	if (data->map[data->pp.y][data->pp.x] == 'C')
		erase_coll(data);
	if (data->totcol == 1 || data->totcol == 0)
		opendoor(data);
	movanim_bonus(data, x, y);
	movene_bonus(data);
	print_text_bonus(data, data->w * 32 - 34, 16);
}
