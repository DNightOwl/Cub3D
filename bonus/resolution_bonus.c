/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:19:28 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 11:06:33 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int			overflow_res(char **info, t_file_sett *f, char *line)
{
	int		i;
	int		j;

	i = skipe_zeros(info[0]);
	j = skipe_zeros(info[1]);
	mlx_get_screen_size(g_game.mlx_ptr, &g_game.r_width, &g_game.r_height);
	if (!check_min_max_res_width(info, i, f, line))
		return (1);
	if (!check_min_max_res_height(info, j, f, line))
		return (1);
	return (0);
}

void		check_res(char *inf, t_file_sett *f, char *line)
{
	size_t	c;
	char	**t;

	c = ft_wcount(inf, ' ');
	if (!ft_strchr(" \n", inf[0]))
		exit(err_conf_handler(ERR_WRONG_EL, f->n_line, f->fd, line));
	else if (c == 0)
		exit(err_conf_handler(ERR_MISS_INF, f->n_line, f->fd, line));
	else if (c == 2)
	{
		if (!(t = ft_split(inf, ' ')))
			exit(err_conf_handler(ERR_FAILED, f->n_line, f->fd, line));
		if (!ft_str_isdigit(t[0]) || !ft_str_isdigit(t[1]))
			exit(err_conf_handler(ERR_DIG_INF, f->n_line, f->fd, line));
		else
		{
			overflow_res(t, f, line);
			g_scan_ele.r += 1;
			g_scan_ele.count += 1;
		}
		free_all(t);
	}
	else
		exit(err_conf_handler(ERR_R_INF, f->n_line, f->fd, line));
}

int			check_min_max_res_width(char **info, int i,
		t_file_sett *f, char *line)
{
	int		nb;
	int		c;

	nb = ft_atoi(info[0] + i);
	c = ft_strlen((info[0] + i));
	if (c <= ft_nbrcount(g_game.r_width))
	{
		if (nb < g_game.r_width)
			g_game.r_width = nb;
		if (nb < g_game.min_res)
			exit(err_conf_handler(ERR_MIN_R, f->n_line, f->fd, line));
	}
	else
		return (0);
	return (1);
}

int			check_min_max_res_height(char **info, int j,
		t_file_sett *f, char *line)
{
	int		nb;
	int		c;

	nb = ft_atoi(info[1] + j);
	c = ft_strlen((info[1] + j));
	if (c <= ft_nbrcount(g_game.r_height))
	{
		if (nb < g_game.r_height)
			g_game.r_height = nb;
		if (nb < g_game.min_res)
			exit(err_conf_handler(ERR_MIN_R, f->n_line, f->fd, line));
	}
	else
		return (0);
	return (1);
}

int			skipe_zeros(char *str)
{
	int		i;

	i = 0;
	while (str[i] == '0')
		i++;
	return (i);
}
