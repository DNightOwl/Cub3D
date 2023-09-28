/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 20:05:55 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 18:29:08 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_img_data		g_img;
t_img_data		g_hud;
t_player			g_player;
t_scan_ele		g_scan_ele;
t_map_data		g_map_data;
t_game_data		g_game;
t_textures		g_texture;
int				g_save;
double			g_fov_angle;
int				g_num_rays;
double			**g_rays;

int			check_dup_ele(void)
{
	if (g_scan_ele.r > 1 || g_scan_ele.no > 1)
		return (1);
	if (g_scan_ele.so > 1 || g_scan_ele.we > 1)
		return (1);
	if (g_scan_ele.ea > 1 || g_scan_ele.s > 1)
		return (1);
	if (g_scan_ele.f > 1 || g_scan_ele.c > 1)
		return (1);
	return (0);
}

int			extension_checker(const char *file_name, const char *ext)
{
	size_t	fn_l;
	size_t	ext_l;

	fn_l = ft_strlen(file_name);
	ext_l = ft_strlen(ext);
	if (!ft_strnstr(ft_strtolower(file_name + (fn_l - ext_l)), ext, ext_l))
		return (0);
	return (1);
}

void		init_ele(void)
{
	g_scan_ele.r = 0;
	g_scan_ele.no = 0;
	g_scan_ele.so = 0;
	g_scan_ele.we = 0;
	g_scan_ele.ea = 0;
	g_scan_ele.s = 0;
	g_scan_ele.f = 0;
	g_scan_ele.c = 0;
	g_scan_ele.map = 0;
	g_scan_ele.sprites = 0;
	g_scan_ele.count = 0;
}

void		empty_line(char *str, char *line, t_file_sett *f, char *mapline)
{
	free(str);
	free(line);
	exit(err_handler(ERR_E_LINE_MAP, f->n_line, f->fd, mapline));
}



int			main(int argc, char **argv)
{
	g_save = 0;
	g_game.min_res = 50;
	if (!(g_game.mlx_ptr = mlx_init()))
		exit(err_conf_handler(ERR_INIT_FAIL, 0, 0, (void*)0));
	if (argc < 2)
		exit(err_handler(ERR_NULL_ARGS, 0, 0, (void*)0));
	else if (argc >= 2 && argc <= 3)
	{
		if (argc == 3 && ft_strlen("--save") == ft_strlen(argv[2])
				&& ft_strncmp(argv[2], "--save", ft_strlen("--save")) == 0)
			g_save = 1;
		else if (argc == 3)
			exit(err_handler(ERR_SND_ARG, 0, 0, (void*)0));
		file_checker_cub(argv);
		game_run();
	}
	else
		exit(err_handler(ERR_LOT_ARGS, 0, 0, (void*)0));
	return (0);
}
