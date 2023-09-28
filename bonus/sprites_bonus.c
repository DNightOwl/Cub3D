/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:21:01 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 16:35:31 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void				draw_sprites(t_sprite *sprites)
{
	int				i;
	int				j;
	double			angle_sprite;
	t_sprite		visible[g_scan_ele.sprites];

	i = 0;
	j = 0;
	while (i < g_scan_ele.sprites)
	{
		angle_sprite = g_player.rotationangle - atan2(sprites[i].y
				- g_player.y, sprites[i].x - g_player.x);
		norm_in_pi_range(&angle_sprite);
		if (angle_sprite < (g_fov_angle / 2 + 0.2))
		{
			sprites[i].angle = angle_sprite;
			sprites[i].dist = distance(sprites[i].x, sprites[i].y);
			visible[j] = sprites[i];
			j++;
		}
		i++;
	}
	sort_sprites(j, visible);
	render_visible_sprites(j, visible);
}

void				render_visible_sprites(int j, t_sprite *visible)
{
	int				i;
	t_sprite		visible_s;
	t_sprite_sett	sp;

	i = 0;
	while (i < j)
	{
		visible_s = visible[i];
		init_sprites_sett(&sp, visible_s);
		render_sprite(&sp, visible_s);
		i++;
	}
}

void				render_sprite(t_sprite_sett *sp, t_sprite visible)
{
	double			x;
	double			y;
	int				*t_color;

	x = sp->sprite_left_x;
	while (x < sp->sprite_right_x)
	{
		sp->text_offset_x = (x - sp->sprite_left_x) * sp->text_width;
		y = sp->sprite_top_y;
		while (y < sp->sprite_bott_y)
		{
			if (x > 0 && x < g_game.r_width && y > 0 && g_game.r_height)
			{
				sp->text_offset_y = (y + sp->d)
					* (TILE_SIZE / sp->sprite_height);
				t_color = (int *)(g_texture.img_sp.addr +
						(sp->text_offset_y * g_texture.img_sp.line_length
						+ sp->text_offset_x * (g_game.bits_per_pixel_8)));
				if (visible.dist < g_rays[(int)x][2] && *t_color != 0x00000000)
					put_sprite_pixel(sp, x, y, t_color);
			}
			y++;
		}
		x++;
	}
}

void				sort_sprites(int nb, t_sprite *visible)
{
	int				i;
	int				j;
	t_sprite		tmp;

	i = 0;
	while (i < nb - 1)
	{
		j = i + 1;
		while (j < nb)
		{
			if (visible[i].dist < visible[j].dist)
			{
				tmp = visible[i];
				visible[i] = visible[j];
				visible[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void				get_sprites(t_sprite *sprites)
{
	int				x;
	int				y;
	int				k;

	x = 0;
	k = 0;
	while (x < g_map_data.nb_cols)
	{
		y = 0;
		while (y < g_map_data.nb_rows)
		{
			if (g_map_data.map[y][x] == '2')
			{
				sprites[k].x = (x + 0.5) * TILE_SIZE;
				sprites[k].y = (y + 0.5) * TILE_SIZE;
				k++;
			}
			y++;
		}
		x++;
	}
}
