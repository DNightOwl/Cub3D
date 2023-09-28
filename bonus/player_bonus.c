/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:18:31 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 16:37:42 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	where_to_look(char ps)
{
	if (ps == 'N')
		g_player.rotationangle = 3 * M_PI_2;
	else if (ps == 'S')
		g_player.rotationangle = M_PI_2;
	else if (ps == 'W')
		g_player.rotationangle = M_PI;
	else if (ps == 'E')
		g_player.rotationangle = 0;
}

void	dup_player(char *t, char **map, int n_line, int player)
{
	if (player > 1)
	{
		free_all(map);
		exit(err_map_handler(ERR_DUP_PLAYER, n_line, t));
	}
}

void	init_player(void)
{
	g_player.x = g_player.x * TILE_SIZE;
	g_player.y = g_player.y * TILE_SIZE;
	g_player.radius = 3;
	g_player.turndirection = 0;
	g_player.walkdirection = 0;
	g_player.walkside = 0;
	g_player.movespeed = 6.0;
	g_player.rotationspeed = 2 * (M_PI / 180);
}

void	player_exist(int player, char **map, int n_line)
{
	if (player == 0)
	{
		free_all(map);
		exit(err_map_handler(ERR_NO_PLAYER, n_line, (void*)0));
	}
}

void	object_collision(double new_px, double new_py)
{
	if (g_map_data.map[(int)(new_py / TILE_SIZE)]
			[(int)(g_player.x / TILE_SIZE)] == '0')
		g_player.y = new_py;
	if (g_map_data.map[(int)(g_player.y / TILE_SIZE)]
			[(int)(new_px / TILE_SIZE)] == '0')
		g_player.x = new_px;
}
