/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:29:12 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/01/09 20:46:28 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# define ERROR "Error\nMapa inválido\n"

# include "./../MLX42/include/MLX42/MLX42.h"
# include "./../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>

typedef struct s_point
{
	int	comp;
	int	y;
	int	x;
	int	pos;
}	t_point;

typedef struct s_image
{
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*cartucho;
	mlx_image_t	*fermin;
	mlx_image_t	*gabi;
	mlx_image_t	*exit;
	mlx_image_t	*ale;
	mlx_image_t	*ale2;
	mlx_image_t	*fermin2;
	mlx_image_t	*text;
}	t_image;

typedef struct s_data
{
	mlx_t	*mlx;
	char	**map;
	char	**cpy;
	int		h;
	int		w;
	int		moves;
	int		totcol;
	int		size;
	t_point	pp;
	t_point	ep;
	t_point	*cp;
	t_point	*ap;
	t_image	image;
}	t_data;

int		mapper(char *argv, t_data *data);
int		comp_rect(t_data *data);
int		comp_close(t_data *data);
int		comp_line(t_data *data);
int		comp_item(t_data *data);
int		comp_path(t_data *data, int y, int x);
int		ft_checker(char *argv, t_data *data);
int		seeimage(t_data *data);
void	createmap(t_data *data, int size);
void	createitem(t_data *data, int size);
void	createitem_bonus(t_data *data, int x, int y, int size);
int		ft_fd(char *str);
void	hook(void *param);

int		compmovx(int posy, int pos, int size, t_data *data);
int		compmovx2(int posy, int pos, int size, t_data *data);
int		compmovy(int posx, int pos, int size, t_data *data);
int		compmovy2(int posx, int pos, int size, t_data *data);

void	movanimene_bonus(t_data *data, int x, int y, int i);
int		compmovye_bonus(int pos, int posx, t_data *data, int i);
int		compmovy2e_bonus(int pos, int posx, t_data *data, int i);
int		compmovxe_bonus(int posy, int pos, t_data *data, int i);
int		compmovx2e_bonus(int posy, int pos, t_data *data, int i);

void	save_enemy_bonus(t_data *data, int aux, int k, int a);
void	enemcoll_bonus(t_data *data, int i);
void	print_text_bonus(t_data *data, int x, int y);
void	movanim_bonus(t_data *data, int x, int y);
void	ft_if_bonus(t_data *data, int i, int y, int x);

void	ft_see(t_data *data);
#endif