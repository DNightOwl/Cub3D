/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:46:08 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 10:59:03 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		get_textures(t_img_data *img_t, t_ray ray)
{
	if (ray.was_hit_vert && ray.look_left)
	{
		*img_t = g_texture.img_w;
		img_t->addr = g_texture.img_w.addr;
	}
	else if (ray.was_hit_vert && !ray.look_left)
	{
		*img_t = g_texture.img_e;
		img_t->addr = g_texture.img_e.addr;
	}
	else if (!ray.was_hit_vert && ray.look_up)
	{
		*img_t = g_texture.img_n;
		img_t->addr = g_texture.img_n.addr;
	}
	else if (!ray.was_hit_vert && !ray.look_up)
	{
		*img_t = g_texture.img_s;
		img_t->addr = g_texture.img_s.addr;
	}
}

void		textures_loader(void)
{
	g_texture.img_n.img = mlx_xpm_file_to_image(
			g_game.mlx_ptr, g_texture.n,
			&g_texture.width, &g_texture.height);
	g_texture.img_s.img = mlx_xpm_file_to_image(
			g_game.mlx_ptr, g_texture.s,
			&g_texture.width, &g_texture.height);
	g_texture.img_w.img = mlx_xpm_file_to_image(
			g_game.mlx_ptr, g_texture.w,
			&g_texture.width, &g_texture.height);
	g_texture.img_e.img = mlx_xpm_file_to_image(
			g_game.mlx_ptr, g_texture.e,
			&g_texture.width, &g_texture.height);
	g_texture.img_sp.img = mlx_xpm_file_to_image(
			g_game.mlx_ptr, g_texture.sp,
			&g_texture.width, &g_texture.height);
}
