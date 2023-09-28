/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_storing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:46:00 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 11:11:49 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			stormap(char *str, int n_line)
{
	char		**map;
	int			y;
	size_t		m_l;

	map = ft_split(str, '|');
	y = 0;
	m_l = 0;
	while (map[y])
	{
		m_l = ft_strlen(map[y]) > m_l ? ft_strlen(map[y]) : m_l;
		y++;
	}
	map_justification(&map, m_l);
	y = ft_wcount(str, '|');
	free(str);
	check_map(map, y, n_line);
	g_map_data.nb_cols = m_l;
	g_map_data.nb_rows = y;
	g_map_data.map = map;
	g_map_data.map[(int)g_player.y][(int)g_player.x] = '0';
}

void			map_justification(char ***map_org, size_t m_l)
{
	int			y;
	size_t		need;
	char		*tmp;
	char		**map;

	map = *map_org;
	y = 0;
	need = 0;
	while (map[y])
	{
		need = m_l - ft_strlen(map[y]);
		while (need)
		{
			tmp = map[y];
			map[y] = ft_strjoin(tmp, " ");
			need--;
			free(tmp);
		}
		y++;
	}
	map_org = &map;
}

void			map_closed_inside(t_map_vars *v_map,
		char xline, char **map, int n_line)
{
	if ((v_map->grid == '0' || v_map->grid == '2') &&
			(v_map->next_grid == ' ' || !ft_strchr("102NSWE", xline)))
	{
		free_all(map);
		exit(err_map_handler(ERR_OPEN_MAP, n_line, (void*)0));
	}
	if (v_map->grid == ' ' && (!ft_strchr("1 ", v_map->next_grid)
				|| !ft_strchr("1 ", xline)))
	{
		free_all(map);
		exit(err_map_handler(ERR_OPEN_MAP, n_line, (void*)0));
	}
}

int				map_line_elements(char *t, int y, char **map, int *player)
{
	int			l;

	l = 0;
	while (t[l])
	{
		if (ft_strchr(" 102NSEW", t[l]))
		{
			*player += ft_strchr("NSEW", t[l]) ? 1 : 0;
			g_player.x = ft_strchr("NSEW", t[l]) ? l + 0.5 : g_player.x;
			g_player.y = ft_strchr("NSEW", t[l]) ? y + 0.5 : g_player.y;
			where_to_look(t[l]);
			g_scan_ele.sprites += ft_strchr("2", t[l]) ? 1 : 0;
		}
		else
		{
			free_all(map);
			return (0);
		}
		l++;
	}
	return (1);
}
