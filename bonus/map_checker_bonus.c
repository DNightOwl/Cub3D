/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:26:43 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 11:26:37 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			check_end_of_map(char *str,
		char *mapline, t_file_sett *f, char *line)
{
	if (mapline[0] == '\0' && !is_map_se(mapline, f->n_line))
	{
		free(str);
		free(line);
		exit(err_handler(ERR_E_LAST_MAP, f->n_line, f->fd, mapline));
	}
	else if (line[0] == '\0' && !is_map_se(line, f->n_line))
	{
		free(str);
		free(line);
		exit(err_handler(ERR_E_LAST_MAP, f->n_line, f->fd, mapline));
	}
	close(f->fd);
	g_scan_ele.map = 1;
}

void			check_map_ele(char **map, int row_l, int n_line, int *player)
{
	int			y;
	char		*t;
	int			t_l;

	y = 0;
	while (++y < row_l)
	{
		t = ft_strtrim(map[y], " ");
		t_l = ft_strlen(t) - 1;
		if (t[0] == '\0')
		{
			free(t);
			continue;
		}
		if (t[0] == '1' && t[t_l] == '1')
		{
			if (!map_line_elements(t, y, map, player))
				exit(err_map_handler(ERR_EL_MAP, n_line, t));
		}
		else if (t[0] != '1' || t[t_l] != '1')
			exit(err_map_handler(ERR_OPEN_MAP, n_line, t));
		dup_player(t, map, n_line, *player);
		n_line++;
	}
}

void			check_map(char **map, int row_l, int n_line)
{
	int			y;
	t_map_vars	v_map;
	int			l;
	int			player;

	player = 0;
	check_first_last_line(map, row_l, n_line);
	check_map_ele(map, row_l, n_line + 1, &player);
	y = 1;
	v_map.xline = map[0];
	while (y < row_l)
	{
		l = -1;
		while (map[y][++l])
		{
			v_map.grid = map[y][l];
			v_map.next_grid = map[y][l + 1];
			map_closed_inside(&v_map, v_map.xline[l], map, n_line);
		}
		v_map.xline = map[y];
		n_line++;
		y++;
	}
	player_exist(player, map, n_line);
}

void			check_first_last_line(char **map, int row_l, int n_line)
{
	int			i;
	int			l;

	i = 0;
	l = row_l - 1;
	while (map[0][i] && map[(l)][i])
	{
		if (map[0][i] != '1' && map[0][i] != ' ')
		{
			free_all(map);
			exit(err_map_handler(ERR_OPEN_MAP, n_line, (void*)0));
		}
		if (map[l][i] != '1' && map[l][i] != ' ')
		{
			if (!ft_strchr(" 102NSEW", map[l][i]))
			{
				free_all(map);
				exit(err_map_handler(ERR_LAST_MAP, n_line + l, (void*)0));
			}
			free_all(map);
			exit(err_map_handler(ERR_OPEN_MAP, n_line + l, (void*)0));
		}
		i++;
	}
}

int				is_wall(double nx, double ny)
{
	int			x;
	int			y;

	y = (int)(ny / TILE_SIZE);
	x = (int)(nx / TILE_SIZE);
	if (g_map_data.map[y][x] == '1')
		return (1);
	return (0);
}
