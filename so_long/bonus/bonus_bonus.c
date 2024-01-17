/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:16:07 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/09 20:47:55 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	save_enemy_bonus(t_data *data, int aux, int k, int a)
{
	if (data->map[aux][k] == 'A')
	{
		data->ap[a].comp = a;
		data->ap[a].x = k;
		data->ap[a].y = aux;
		data->ap[a].pos = rand() % 50;
	}
}

void	enemcoll_bonus(t_data *data, int i)
{
	if (data->pp.y == data->ap[i].y && data->pp.x == data->ap[i].x)
		mlx_close_window(data->mlx);
}

void	print_text_bonus(t_data *data, int x, int y)
{
	char	*txt;

	txt = ft_itoa(data->moves);
	mlx_delete_image(data->mlx, data->image.text);
	data->image.text = mlx_put_string(data->mlx, txt, x, y);
	free(txt);
}

void	movanim_bonus(t_data *data, int x, int y)
{
	int	ctrlx;
	int	ctrly;

	ctrlx = data->image.fermin->instances[0].x;
	ctrly = data->image.fermin->instances[0].y;
	if (x != ctrlx || y != ctrly)
	{
		data->image.fermin2->enabled = true;
		data->image.fermin->enabled = false;
	}
	else
	{
		data->image.fermin2->enabled = false;
		data->image.fermin->enabled = true;
	}
}

void	ft_if_bonus(t_data *data, int i, int y, int x)
{
	if (!ft_strchr("1AEC", data->map[data->ap[i].y + y][data->ap[i].x + x]))
	{
		data->map[data->ap[i].y][data->ap[i].x] = '0';
		data->ap[i].y = y + data->ap[i].y;
		data->ap[i].x = x + data->ap[i].x;
		data->map[data->ap[i].y][data->ap[i].x] = 'A';
	}
}
