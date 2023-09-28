/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:10:12 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 09:33:31 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			scan_file_cub(t_file_sett *f)
{
	char		*line;
	int			t;
	int			type;

	type = 0;
	f->n_line = 1;
	while ((t = get_next_line(f->fd, &line)) == 1)
	{
		if (line[0] != '\0')
			scan_file_el(f, line, type);
		if (check_dup_ele())
			exit(err_handler(ERR_DUP_EL, f->n_line, f->fd, line));
		f->n_line++;
	}
	if (g_scan_ele.map == 0)
		exit(err_handler(ERR_MISS_MAP, f->n_line, f->fd, line));
	close(f->fd);
	free(line);
}

void			file_checker_cub(char **args)
{
	t_file_sett	f;

	if ((f.fd = open(args[1], O_RDONLY)) < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(err_handler(ERR_FRS_ARG, 0, f.fd, (void*)0));
	}
	if (extension_checker(args[1], ".cub") && f.fd >= 0)
	{
		init_ele();
		scan_file_cub(&f);
	}
}

void			scan_file_el(t_file_sett *f, char *line, int type)
{
	if ((ft_strchr("RSFC", line[0]) ||
				(ft_strchr("NSWE", line[0]) && ft_strchr("OEA", line[1]))))
		check_elements(f, line);
	else if ((ft_strchr(" \t\v\n\f\r", line[0]) ||
				ft_strchr(" \t\v\n\f\r", line[ft_strlen(line) - 1])) &&
					g_scan_ele.count < 8)
	{
		if (is_valid_empty_line(line))
			type = f->n_line;
		else if (is_map_se(line, f->n_line))
			scan_file_map(f, line, type);
		else
			exit(err_handler(ERR_SPACE_EL, f->n_line, f->fd, line));
	}
	else if (is_map_se(line, f->n_line))
		scan_file_map(f, line, type);
	else
		exit(err_handler(ERR_EL, f->n_line, f->fd, line));
}

void			check_elements(t_file_sett *f, char *line)
{
	if (line[0] == 'R')
		check_res(line + 1, f, line);
	if (line[0] == 'N' && line[1] == 'O' && (g_scan_ele.no = g_scan_ele.no + 1))
		g_texture.n = check_path(line + 2, f, line);
	if (line[0] == 'S')
	{
		if (line[1] == 'O' && (g_scan_ele.so = g_scan_ele.so + 1))
			g_texture.s = check_path(line + 2, f, line);
		else
		{
			g_texture.sp = check_path(line + 1, f, line);
			g_scan_ele.s += 1;
		}
	}
	if (line[0] == 'W' && line[1] == 'E' && (g_scan_ele.we = g_scan_ele.we + 1))
		g_texture.w = check_path(line + 2, f, line);
	if (line[0] == 'E' && line[1] == 'A' && (g_scan_ele.ea = g_scan_ele.ea + 1))
		g_texture.e = check_path(line + 2, f, line);
	if (line[0] == 'C' && (g_scan_ele.c = g_scan_ele.c + 1))
		g_game.ceilling_color = get_color(line + 1, f, line);
	if (line[0] == 'F' && (g_scan_ele.f = g_scan_ele.f + 1))
		g_game.floor_color = get_color(line + 1, f, line);
}

char			*check_path(char *path, t_file_sett *f, char *line)
{
	void		*img;
	int			img_w;
	int			img_h;

	if (!ft_strchr(" \n", path[0]))
		exit(err_conf_handler(ERR_WRONG_EL, f->n_line, f->fd, line));
	if (ft_strchr(path, '\t'))
		exit(err_conf_handler(ERR_SPACE_INF, f->n_line, f->fd, line));
	while (*path++ && !(img = mlx_xpm_file_to_image(
					g_game.mlx_ptr, path, &img_w, &img_h)))
	{
		if (path[0] != ' ')
			break ;
	}
	if (!img)
		exit(err_conf_handler(ERR_XPM, f->n_line, f->fd, line));
	else
	{
		g_scan_ele.count += 1;
		mlx_destroy_image(g_game.mlx_ptr, img);
	}
	return (path);
}
