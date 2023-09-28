/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:15:21 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 10:46:37 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		textures_init_addrs(void)
{
	g_texture.img_n.addr = mlx_get_data_addr(
			g_texture.img_n.img,
			&g_texture.img_n.bits_per_pixel,
			&g_texture.img_n.line_length,
			&g_texture.img_n.endian);
	g_texture.img_s.addr = mlx_get_data_addr(
			g_texture.img_s.img,
			&g_texture.img_s.bits_per_pixel,
			&g_texture.img_s.line_length,
			&g_texture.img_s.endian);
	g_texture.img_w.addr = mlx_get_data_addr(
			g_texture.img_w.img,
			&g_texture.img_w.bits_per_pixel,
			&g_texture.img_w.line_length,
			&g_texture.img_w.endian);
	g_texture.img_e.addr = mlx_get_data_addr(
			g_texture.img_e.img,
			&g_texture.img_e.bits_per_pixel,
			&g_texture.img_e.line_length,
			&g_texture.img_e.endian);
	g_texture.img_sp.addr = mlx_get_data_addr(
			g_texture.img_sp.img,
			&g_texture.img_sp.bits_per_pixel,
			&g_texture.img_sp.line_length,
			&g_texture.img_sp.endian);
}

void		init_sprites_sett(t_sprite_sett *sp, t_sprite visible_s)
{
	double	dist_plane;

	dist_plane = (g_game.r_width / 2) / tan(g_fov_angle / 2);
	sp->corr_distance = visible_s.dist * cos(visible_s.angle);
	sp->sprite_height = (TILE_SIZE / sp->corr_distance) * dist_plane;
	sp->sprite_width = sp->sprite_height;
	sp->sprite_top_y = (g_game.r_height / 2) - (sp->sprite_height / 2);
	sp->sprite_top_y = (sp->sprite_top_y < 0) ? 0 : sp->sprite_top_y;
	sp->sprite_bott_y = (g_game.r_height / 2) + (sp->sprite_height / 2);
	sp->sprite_bott_y = (sp->sprite_bott_y > g_game.r_height)
		? g_game.r_height : sp->sprite_bott_y;
	sp->angle_sp = atan2(visible_s.y - g_player.y,
			visible_s.x - g_player.x) - g_player.rotationangle;
	sp->sprite_x = tan(sp->angle_sp) * dist_plane;
	sp->sprite_left_x = (g_game.r_width / 2)
		+ sp->sprite_x - (sp->sprite_width / 2);
	sp->sprite_right_x = (g_game.r_width / 2)
		+ sp->sprite_x + (sp->sprite_width / 2);
	sp->text_width = ((double)TILE_SIZE / sp->sprite_width);
	sp->d = (sp->sprite_height / 2) - (g_game.r_height / 2);
}

void		setting_wall_var(int col, t_wall_sett *wall, t_ray ray)
{
	wall->corr_dist = ray.distance * cos(ray.rayangle - g_player.rotationangle);
	wall->dis_plane = (g_game.r_width / 2) / tan(g_fov_angle / 2);
	wall->wall_strip_hight = (TILE_SIZE / wall->corr_dist) * wall->dis_plane;
	wall->startx = col * g_game.wall_strip_width;
	wall->starty = (g_game.r_height / 2) - (wall->wall_strip_hight / 2);
	wall->endy = (wall->wall_strip_hight / 2) + (g_game.r_height / 2);
	wall->cof_dist_top = (wall->wall_strip_hight / 2) - (g_game.r_height / 2);
	wall->starty = wall->starty < 0 ? 0 : wall->starty;
	wall->endy = wall->endy >= g_game.r_height ? g_game.r_height : wall->endy;
}

void		init_ray(t_ray *ray, double *rayangle)
{
	ray->rayangle = radian_norme(*rayangle);
	ray->wallhit_x = 0.0;
	ray->wallhit_y = 0.0;
	ray->distance = 0.0;
	ray->was_hit_vert = 0;
	ray->look_up = 0;
	ray->look_left = 0;
}

void		init_game(void)
{
	g_fov_angle = 60 * (M_PI / 180);
	g_game.wall_strip_width = 1;
	g_num_rays = (g_game.r_width / g_game.wall_strip_width);
	g_rays = malloc(sizeof(double*) * g_num_rays);
	g_game.bits_per_pixel_8 = g_texture.img_n.bits_per_pixel / 8;
	g_map_data.width = g_map_data.nb_cols * TILE_SIZE;
	g_map_data.height = g_map_data.nb_rows * TILE_SIZE;
}
