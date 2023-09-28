/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horz_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:14:31 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 16:42:32 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		h_intercepts(t_hit *hit, double x, double y, double *rayangle)
{
	double	normrad;

	normrad = radian_norme(*rayangle);
	if (normrad < M_PI)
		hit->yintercept = ceil(y / TILE_SIZE) * TILE_SIZE;
	else
		hit->yintercept = floor(y / TILE_SIZE) * TILE_SIZE;
	hit->xintercept = x + ((hit->yintercept - y) / tan(*rayangle));
}

void		h_cal_steps(t_hit *hit, double rayangle)
{
	if (rayangle < M_PI)
		hit->ystep = TILE_SIZE;
	else
		hit->ystep = TILE_SIZE * -1;
	hit->xstep = TILE_SIZE / tan(rayangle);
	if (rayangle < (M_PI_2) || rayangle > (3 * M_PI_2))
		hit->xstep *= hit->xstep < 0 ? -1 : 1;
	else
		hit->xstep *= hit->xstep > 0 ? -1 : 1;
}

int			get_next_hor_hit(t_hit *hit, t_ray *ray,
		double *h_wall_hit_x, double *h_wall_hit_y)
{
	double	h_next_hit_x;
	double	h_next_hit_y;
	int		is_up;

	h_next_hit_x = hit->xintercept;
	h_next_hit_y = hit->yintercept;
	is_up = ray->rayangle > M_PI ? 1 : 0;
	ray->look_up = is_up;
	while (h_next_hit_x > 0 && h_next_hit_x < g_map_data.width
			&& h_next_hit_y > 0 && h_next_hit_y < g_map_data.height)
	{
		if (is_wall(h_next_hit_x, (h_next_hit_y - is_up)))
		{
			*h_wall_hit_x = h_next_hit_x;
			*h_wall_hit_y = h_next_hit_y;
			return (1);
		}
		else
		{
			h_next_hit_x += hit->xstep;
			h_next_hit_y += hit->ystep;
		}
	}
	return (0);
}

int			horizontal_intersection(t_ray *ray,
		double *h_wall_hit_x, double *h_wall_hit_y)
{
	t_hit	hit;
	int		is_wall_hit_h;

	is_wall_hit_h = 0;
	h_intercepts(&hit, g_player.x, g_player.y, &(ray->rayangle));
	h_cal_steps(&hit, ray->rayangle);
	is_wall_hit_h = get_next_hor_hit(&hit, ray, h_wall_hit_x, h_wall_hit_y);
	return (is_wall_hit_h);
}

int			color_shade(double dist, int color, int shade_range)
{
	int			r;
	int			g;
	int			b;

	r = (color & (0xFF << 16)) >> 16;
	g = (color & (0xFF << 8)) >> 8;
	b = (color & (0xFF));
	if (dist >= shade_range)
		return (0);
	else if (dist >= 0 && dist < shade_range)
	{
		r -= r * (dist / shade_range);
		g -= g * (dist / shade_range);
		b -= b * (dist / shade_range);
	}
	return (create_trgb(0, r, g, b));
}
