/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:53:42 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/11 18:40:35 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free (str);
	return (NULL);
}

int	so_long(t_data *data, int size)
{
	if (seeimage(data) == 1)
		return (ft_error(data), 1);
	createmap(data, size);
	createitem(data, size);
	data->totcol = data->image.cartucho->count + 1;
	return (0);
}

/* void	ft_leaks(void)
{
	system("leaks -q so_long");
} */

void	ft_error(t_data *data)
{
	if (data->map)
		ft_free(data->map);
	if (data->cp)
		free(data->cp);
	if (data->cpy)
		ft_free(data->cpy);
}
	//atexit(ft_leaks);

int	main(int argc, char **argv)
{
	t_data	data;
	int		size;

	size = 64;
	data.map = NULL;
	data.cpy = NULL;
	data.cp = NULL;
	data.moves = 0;
	if (argc != 2)
		return (write(2, "Error\nNúmero de argumentos erróneos\n", 39), 1);
	if (ft_checker(argv[1], &data) == 1)
		return (ft_error(&data), 1);
	data.mlx = mlx_init((data.w - 1) * size, data.h * size, argv[1], true);
	if (so_long(&data, size))
		return (1);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_free(data.map);
	ft_free(data.cpy);
	free(data.cp);
	return (0);
}
