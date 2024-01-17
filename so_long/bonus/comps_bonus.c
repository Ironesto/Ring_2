/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comps_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:46:07 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/09 19:59:36 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	comp_rect(t_data *data)
{
	int	aux;

	data->h = 0;
	data->w = ft_strlen(data->map[data->h]);
	aux = data->w;
	while (data->map[data->h])
	{
		if (data->map[data->h] != NULL && data->w != aux)
			return (write(2, "Error\nMapa no rectangular\n", 26), 1);
		data->h++;
		if (data->map[data->h] != NULL)
			data->w = ft_strlen(data->map[data->h]);
	}
	return (0);
}

int	comp_close(t_data *data)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	while (data->map[0][k] != '\n')
	{
		if (data->map[0][k] != '1')
			return (1);
		k++;
	}
	while (i < data->h)
	{
		if (data->map[i][k - 1] != '1' || data->map[i][0] != '1')
			return (1);
		i++;
	}
	k = 0;
	while (data->map[data->h - 1][k] != '\n')
	{
		if (data->map[data->h - 1][k] != '1')
			return (1);
		k++;
	}
	return (0);
}

int	comp_line(t_data *data)
{
	int	i;
	int	k;
	int	a;

	i = 0;
	a = 0;
	while (data->map[++i] != NULL)
	{
		k = data->w - 2;
		while (k > 0)
		{
			if (data->map[i][k] == 'C')
				data->totcol++;
			if (data->map[i][k] == 'A')
				a++;
			if (!ft_strchr("10CAPE", data->map[i][k]))
				return (1);
			k--;
		}
	}
	if (data->totcol == 0 || a == 0)
		return (1);
	data->cp = malloc(sizeof(t_point) * data->totcol);
	data->ap = malloc(sizeof(t_point) * a);
	return (0);
}

static int	save_point(t_data *data, int aux, int k, int c)
{
	if (data->map[aux][k] == 'P')
	{
		data->pp.comp++;
		data->pp.x = k;
		data->pp.y = aux;
	}
	else if (data->map[aux][k] == 'E')
	{
		data->ep.comp++;
		data->ep.x = k;
		data->ep.y = aux;
	}
	else if (data->map[aux][k] == 'C')
	{
		data->cp[c].comp = c;
		data->cp[c].x = k;
		data->cp[c].y = aux;
		data->cp[c].pos = 0;
	}
	if (data->pp.comp > 1)
		return (write(2, "Error\nDemasiados jugadores\n", 27), 1);
	if (data->ep.comp > 1)
		return (write(2, "Error\nDemasiadas salidas\n", 25), 1);
	return (0);
}

int	comp_item(t_data *data)
{
	int	k;
	int	aux;
	int	c;
	int	a;

	c = 0;
	a = 0;
	aux = -1;
	while (++aux < data->h - 1)
	{
		k = 1;
		while (k < data->w - 2)
		{
			if (save_point(data, aux, k, c) == 1)
				return (1);
			if (data->map[aux][k] == 'C')
				c++;
			save_enemy_bonus(data, aux, k, a);
			if (data->map[aux][k] == 'A')
				a++;
			k++;
		}
	}
	return (0);
}
