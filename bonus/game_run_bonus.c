/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:13:31 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 16:38:07 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			game_run(void)
{
	t_sprite	*sprites;

	textures_loader();
	textures_init_addrs();
	init_player();
	sprites = malloc(sizeof(t_sprite) * g_scan_ele.sprites);
	get_sprites(sprites);
	init_game();
	g_game.plane_shade = SHADE_RANGE;
	if (g_save)
		update_game(sprites);
	g_game.mlx_win = mlx_new_window(g_game.mlx_ptr,
			g_game.r_width, g_game.r_height, WIN_TITLE);
	mlx_hook(g_game.mlx_win, KEYPRESS, (1L<<0), key_pressed, (void *)0);
	mlx_hook(g_game.mlx_win, KEYRELEASE, (1L<<1), key_released, (void *)0);
	mlx_hook(g_game.mlx_win, DESTROYNOTIFY, (1L<<17), close_win, (void *)0);
	mlx_loop_hook(g_game.mlx_ptr, update_game, sprites);
	mlx_loop(g_game.mlx_ptr);
}

int				update_game(t_sprite *sprites)
{
	double		new_px;
	double		new_py;
	double		movestep;
	double		moveside;

	g_img.img = mlx_new_image(g_game.mlx_ptr, g_game.r_width, g_game.r_height);
	g_img.addr = mlx_get_data_addr(g_img.img,
			&g_img.bits_per_pixel, &g_img.line_length, &g_img.endian);
	g_player.rotationangle += (double)g_player.turndirection
		* (double)g_player.rotationspeed;
	g_player.rotationangle = radian_norme(g_player.rotationangle);
	movestep = g_player.walkdirection * g_player.movespeed;
	moveside = fabs(g_player.walkside) * M_PI_2;
	movestep = moveside != 0 ?
		g_player.walkside * g_player.movespeed : movestep;
	new_px = g_player.x + cos(g_player.rotationangle + moveside) * movestep;
	new_py = g_player.y + sin(g_player.rotationangle + moveside) * movestep;
	object_collision(new_px, new_py);
	cast_all_rays();
	draw_sprites(sprites);
	if (g_save)
		game_save();
	mlx_put_image_to_window(g_game.mlx_ptr, g_game.mlx_win, g_img.img, 0, 0);
	mlx_destroy_image(g_game.mlx_ptr, g_img.img);
	return (0);
}

int				close_win(int keycode)
{
	exit(keycode);
	return (0);
}

int				key_pressed(int keycode)
{
	if (keycode == WALK)
		g_player.walkdirection = 1;
	if (keycode == BACK)
		g_player.walkdirection = -1;
	if (keycode == TURNRIGHT)
		g_player.turndirection = 1;
	if (keycode == TURNLEFT)
		g_player.turndirection = -1;
	if (keycode == LEFT)
		g_player.walkside = -1;
	if (keycode == RIGHT)
		g_player.walkside = 1;
	if (keycode == ESC)
		close_win(keycode);
	return (0);
}

int				key_released(int keycode)
{
	if (keycode == WALK)
		g_player.walkdirection = 0;
	if (keycode == BACK)
		g_player.walkdirection = 0;
	if (keycode == TURNRIGHT)
		g_player.turndirection = 0;
	if (keycode == TURNLEFT)
		g_player.turndirection = 0;
	if (keycode == LEFT)
		g_player.walkside = 0;
	if (keycode == RIGHT)
		g_player.walkside = 0;
	return (0);
}
