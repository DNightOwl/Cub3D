/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:09:13 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 16:39:02 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int				color_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (create_trgb(0, r, g, b));
}

void			check_color(char *param, int *color, t_file_sett *f, char *line)
{
	size_t		c;
	char		**t;

	if (param[0] != ',' && param[ft_strlen(param) - 1] != ',' &&
			(c = ft_wcount(param, ',')) == 3)
	{
		if (!(t = ft_split(param, ',')))
			exit(err_conf_handler(ERR_FAILED, f->n_line, f->fd, line));
		if (!ft_str_isdigit(t[0]) || !ft_str_isdigit(t[1]) ||
				!ft_str_isdigit(t[2]))
		{
			free_all(t);
			free(param);
			exit(err_conf_handler(ERR_DIGIT_COL, f->n_line, f->fd, line));
		}
		if ((*color = color_range(ft_atoi(t[0]),
						ft_atoi(t[1]), ft_atoi(t[2]))) == -1)
		{
			free_all(t);
			free(param);
			exit(err_conf_handler(ERR_DIGIT_COL, f->n_line, f->fd, line));
		}
		free_all(t);
	}
}

void			is_count_colors(char *param, t_file_sett *f, char *line)
{
	int			k;
	int			i;

	k = 0;
	i = 0;
	while (param[i] != '\0')
	{
		if (param[i] == ',')
			k++;
		if (k > 2)
		{
			free(param);
			exit(err_conf_handler(ERR_PARAM_COL, f->n_line, f->fd, line));
		}
		i++;
	}
}

int				get_color(char *param, t_file_sett *f, char *line)
{
	size_t		c;
	int			color;

	if (!ft_strchr(" \n", param[0]))
		exit(err_conf_handler(ERR_WRONG_EL, f->n_line, f->fd, line));
	if ((c = ft_wcount(param, ' ')) == 1)
		param = ft_strtrim(param, " ");
	else if ((c = ft_wcount(param, ' ')) == 0)
		exit(err_conf_handler(ERR_MISS_INF, f->n_line, f->fd, line));
	else
		exit(err_conf_handler(ERR_COMA_COL, f->n_line, f->fd, line));
	if ((c = ft_wcount(param, ',')) != 3)
		exit(err_conf_handler(ERR_PARAM_COL, f->n_line, f->fd, line));
	if (ft_strchr(param, '\t') || ft_strchr(param, ' '))
	{
		free(param);
		exit(err_conf_handler(ERR_COMA_COL, f->n_line, f->fd, line));
	}
	is_count_colors(param, f, line);
	check_color(param, &color, f, line);
	g_scan_ele.count += 1;
	free(param);
	return (color);
}

int				create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
