/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:46:32 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 11:43:22 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void				cast_ray(t_ray *ray)
{
	t_wall_hit		horiz;
	t_wall_hit		verti;

	horiz.is_wall_hit = horizontal_intersection(ray,
			&horiz.wall_hit_x, &horiz.wall_hit_y);
	verti.is_wall_hit = vertical_intersection(ray,
			&verti.wall_hit_x, &verti.wall_hit_y);
	horiz.hit_dis = horiz.is_wall_hit ?
		distance(horiz.wall_hit_x, horiz.wall_hit_y) : MAX_NUM;
	verti.hit_dis = verti.is_wall_hit ?
		distance(verti.wall_hit_x, verti.wall_hit_y) : MAX_NUM;
	ray->wallhit_x = horiz.hit_dis < verti.hit_dis ?
		horiz.wall_hit_x : verti.wall_hit_x;
	ray->wallhit_y = horiz.hit_dis < verti.hit_dis ?
		horiz.wall_hit_y : verti.wall_hit_y;
	ray->distance = horiz.hit_dis < verti.hit_dis ?
		horiz.hit_dis : verti.hit_dis;
	ray->was_hit_vert = verti.hit_dis < horiz.hit_dis;
}

void				cast_all_rays(void)
{
	int				col;
	t_wall_sett		wall;
	t_ray			ray;
	t_img_data		img_t;
	int				*t_color;

	col = 0;
	t_color = NULL;
	wall.rayangle = g_player.rotationangle - (g_fov_angle / 2);
	while (col < g_num_rays)
	{
		init_ray(&ray, &(wall.rayangle));
		cast_ray(&ray);
		g_rays[col] = malloc(sizeof(double) * 4);
		g_rays[col][0] = ray.wallhit_x;
		g_rays[col][1] = ray.wallhit_y;
		g_rays[col][2] = ray.distance;
		setting_wall_var(col, &wall, ray);
		get_textures(&img_t, ray);
		draw_ceilling(col, 0, wall.starty, g_game.ceilling_color);
		draw_strip(ray, wall, img_t, t_color);
		draw_floor(col, wall.endy, g_game.r_height, g_game.floor_color);
		wall.rayangle += g_fov_angle / g_num_rays;
		col++;
	}
}
