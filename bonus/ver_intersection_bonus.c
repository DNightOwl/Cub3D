/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ver_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:22:40 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 16:42:17 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		v_intercepts(t_hit *hit, double x, double y, double *rayangle)
{
	double	normrad;

	normrad = radian_norme(*rayangle);
	if (normrad < (M_PI_2) || normrad > (3 * M_PI_2))
		hit->xintercept = ceil(x / TILE_SIZE) * TILE_SIZE;
	else
		hit->xintercept = floor(x / TILE_SIZE) * TILE_SIZE;
	hit->yintercept = y + ((hit->xintercept - x) * tan(*rayangle));
}

void		v_cal_steps(t_hit *hit, double rayangle)
{
	hit->ystep = TILE_SIZE * tan(rayangle);
	if (rayangle < M_PI)
		hit->ystep *= hit->ystep < 0 ? -1 : 1;
	else
		hit->ystep *= hit->ystep > 0 ? -1 : 1;
	if (rayangle < (M_PI_2) || rayangle > (3 * M_PI_2))
		hit->xstep = TILE_SIZE;
	else
		hit->xstep = TILE_SIZE * -1;
}

int			get_next_ver_hit(t_hit *hit, t_ray *ray,
		double *v_wall_hit_x, double *v_wall_hit_y)
{
	double	v_next_hit_x;
	double	v_next_hit_y;
	int		is_left;

	v_next_hit_x = hit->xintercept;
	v_next_hit_y = hit->yintercept;
	is_left = (ray->rayangle < (M_PI_2) ||
			ray->rayangle > (3 * M_PI_2)) ? 0 : 1;
	ray->look_left = is_left;
	while (v_next_hit_x > 0 && v_next_hit_x < g_map_data.width &&
			v_next_hit_y > 0 && v_next_hit_y < g_map_data.height)
	{
		if (is_wall((v_next_hit_x - is_left), v_next_hit_y))
		{
			*v_wall_hit_x = v_next_hit_x;
			*v_wall_hit_y = v_next_hit_y;
			return (1);
		}
		else
		{
			v_next_hit_x += hit->xstep;
			v_next_hit_y += hit->ystep;
		}
	}
	return (0);
}

int			vertical_intersection(t_ray *ray,
		double *v_wall_hit_x, double *v_wall_hit_y)
{
	t_hit	hit;
	int		is_wall_hit_v;

	is_wall_hit_v = 0;
	v_intercepts(&hit, g_player.x, g_player.y, &(ray->rayangle));
	v_cal_steps(&hit, ray->rayangle);
	is_wall_hit_v = get_next_ver_hit(&hit, ray, v_wall_hit_x, v_wall_hit_y);
	return (is_wall_hit_v);
}

void		put_sprite_pixel(t_sprite_sett *sp,
		int x, int y, int *t_color)
{
	my_mlx_pixel_put(&g_img, x, y,
			color_shade(sp->corr_distance, *t_color, SHADE_RANGE));
}
