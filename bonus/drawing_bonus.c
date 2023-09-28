/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:12:09 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/05 12:14:00 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		draw_strip(t_ray ray, t_wall_sett wall,
			t_img_data img_t, int *t_color)
{
	int		text_offset_x;
	int		text_offset_y;
	double	i;
	double	j;

	if (ray.was_hit_vert)
		text_offset_x = (int)ray.wallhit_y % TILE_SIZE;
	else
		text_offset_x = (int)ray.wallhit_x % TILE_SIZE;
	j = 0;
	while (j < g_game.wall_strip_width)
	{
		i = wall.starty;
		while (i < wall.endy)
		{
			text_offset_y = (i + wall.cof_dist_top)
				* ((double)TILE_SIZE / wall.wall_strip_hight);
			t_color = (int *)(img_t.addr + (text_offset_y * img_t.line_length
						+ text_offset_x * (g_game.bits_per_pixel_8)));
			my_mlx_pixel_put(&g_img, wall.startx + j, i,
					color_shade(wall.corr_dist, *t_color, SHADE_RANGE));
			i++;
		}
		j++;
	}
}

void		draw_ceilling(int col, double start, double end, int color)
{
	double	j;
	double	y;

	j = 0;
	while (j < g_game.wall_strip_width)
	{
		y = start;
		while (y < end)
		{
			my_mlx_pixel_put(&g_img, col + j, y,
					color_shade(y, color, g_game.plane_shade));
			y++;
		}
		j++;
	}
}

void		draw_floor(int col, double start, double end, int color)
{
	double	j;
	double	y;

	j = 0;
	while (j < g_game.wall_strip_width)
	{
		y = start;
		while (y < end)
		{
			my_mlx_pixel_put(&g_img, col + j, y, color);
			y++;
		}
		j++;
	}
}

void		my_mlx_pixel_put(t_img_data *img_data, int x, int y, int color)
{
	char	*dst;

	dst = img_data->addr + (y * img_data->line_length
			+ x * (img_data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
