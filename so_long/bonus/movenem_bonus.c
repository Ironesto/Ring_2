/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movenem_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:22:10 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/08 20:35:36 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	movanimene_bonus(t_data *data, int x, int y, int i)
{
	int	ctrlx;
	int	ctrly;

	ctrlx = data->image.ale2->instances[i].x;
	ctrly = data->image.ale2->instances[i].y;
	if (x != ctrlx || y != ctrly)
	{
		data->image.ale2->instances[i].enabled = true;
		data->image.ale->instances[i].enabled = false;
	}
	else
	{
		data->image.ale2->instances[i].enabled = false;
		data->image.ale->instances[i].enabled = true;
		data->image.ale->instances[i].x = ctrlx;
		data->image.ale->instances[i].y = ctrly;
	}
}

int	compmovye_bonus(int pos, int posx, t_data *data, int i)
{
	int			aux;

	aux = (pos + 20) / data->size;
	if (data->map[data->ap[i].y - 1][data->ap[i].x] == '1'
		&& aux < data->ap[i].y)
		return (1);
	if ((pos + 20) / data->size < data->ap[i].y
		&& (posx + 47) / data->size > data->ap[i].x
		&& data->map[data->ap[i].y - 1][data->ap[i].x + 1] == '1'
			&& data->map[data->ap[i].y][data->ap[i].x + 1] != '1')
		return (1);
	if ((pos + 20) / data->size < data->ap[i].y
		&& (posx + 15) / data->size < data->ap[i].x
		&& data->map[data->ap[i].y - 1][data->pp.x - 1] == '1'
			&& data->map[data->ap[i].y][data->pp.x - 1] != '1')
		return (1);
	if ((pos + 32) / data->size < data->ap[i].y)
	{
		if (!ft_strchr("1AEC", data->map[data->ap[i].y - 1][data->ap[i].x]))
			ft_if_bonus(data, i, -1, 0);
		else
			return (1);
	}
	return (0);
}

int	compmovy2e_bonus(int pos, int posx, t_data *data, int i)
{
	if ((pos + 63) / data->size > data->ap[i].y
		&& data->map[data->ap[i].y + 1][data->ap[i].x] == '1')
		return (1);
	if ((pos + 63) / data->size > data->ap[i].y
		&& (posx + 47) / data->size > data->ap[i].x
		&& data->map[data->ap[i].y + 1][data->ap[i].x + 1] == '1'
			&& data->map[data->ap[i].y][data->ap[i].x + 1] != '1')
		return (1);
	if ((pos + 63) / data->size > data->ap[i].y
		&& (posx + 15) / data->size < data->ap[i].x
		&& data->map[data->ap[i].y + 1][data->ap[i].x - 1] == '1'
			&& data->map[data->ap[i].y][data->ap[i].x - 1] != '1')
		return (1);
	if ((pos + 32) / data->size > data->ap[i].y)
	{
		if (!ft_strchr("1AEC", data->map[data->ap[i].y + 1][data->ap[i].x]))
			ft_if_bonus(data, i, 1, 0);
		else
			return (1);
	}
	return (0);
}

int	compmovxe_bonus(int posy, int pos, t_data *data, int i)
{
	int	aux;

	aux = (pos + 12) / data->size;
	if (data->map[data->ap[i].y][data->ap[i].x - 1] == '1'
		&& (pos + 12) / data->size < data->ap[i].x)
		return (1);
	if (aux < data->ap[i].x && (posy + 23) / data->size < data->ap[i].y
		&& data->map[data->ap[i].y - 1][data->ap[i].x - 1] == '1'
			&& data->map[data->ap[i].y - 1][data->ap[i].x] != '1')
		return (1);
	if (aux < data->ap[i].x && (posy + 61) / data->size > data->ap[i].y
		&& data->map[data->ap[i].y + 1][data->ap[i].x - 1] == '1'
			&& data->map[data->ap[i].y + 1][data->ap[i].x] != '1')
		return (1);
	if ((pos + 32) / data->size < data->ap[i].x)
	{
		if (!ft_strchr("1AEC", data->map[data->ap[i].y][data->ap[i].x - 1]))
			ft_if_bonus(data, i, 0, -1);
		else
			return (1);
	}
	return (0);
}

int	compmovx2e_bonus(int posy, int pos, t_data *data, int i)
{
	int	aux;

	aux = (pos + 50) / data->size;
	if (aux > data->ap[i].x
		&& data->map[data->ap[i].y][data->ap[i].x + 1] == '1')
		return (1);
	if (aux > data->ap[i].x && (posy + 23) / data->size < data->ap[i].y
		&& data->map[data->ap[i].y - 1][data->ap[i].x + 1] == '1'
			&& data->map[data->ap[i].y - 1][data->ap[i].x] != '1')
		return (1);
	if (aux > data->ap[i].x && (posy + 61) / data->size > data->ap[i].y
		&& data->map[data->ap[i].y + 1][data->ap[i].x + 1] == '1'
			&& data->map[data->ap[i].y + 1][data->ap[i].x] != '1')
		return (1);
	if ((pos + 20) / data->size > data->ap[i].x && aux > data->ap[i].x)
	{
		if (!ft_strchr("1AEC", data->map[data->ap[i].y][data->ap[i].x + 1]))
			ft_if_bonus(data, i, 0, 1);
		else
			return (1);
	}
	return (0);
}
