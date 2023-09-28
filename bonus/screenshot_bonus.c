/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:20:13 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 11:32:09 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			game_save(void)
{
	int			i;
	int			j;
	int			pixel_nb;
	int			fd;

	i = 0;
	j = i;
	fd = write_screenshot_header();
	pixel_nb = (g_img.line_length / 4) * g_game.r_height;
	while (i < pixel_nb)
	{
		if ((i % (g_img.line_length / 4)) < g_game.r_width)
			write(fd, g_img.addr + j, 3);
		i++;
		j += 4;
	}
	ft_putstr_fd("the screenshot was saved,", 1);
	ft_putstr_fd(SCREENSHOT_NAME, 1);
	ft_putstr_fd("\n", 1);
	close(fd);
	exit(0);
}

int				write_screenshot_header(void)
{
	int			fd;
	static int	header[] = {
		0,
		0, 0x36, 0x28, 0,
		0,
		0x180001, 0, 0, 0x002e23, 0x002e23,
		0,
		0,
	};

	fd = open(SCREENSHOT_NAME, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		exit(1);
	header[0] = 2 + sizeof(header) + 3 * g_game.r_height * (g_game.r_width + 1);
	header[4] = g_game.r_width;
	header[5] = -g_game.r_height;
	write(fd, "BM", 2);
	write(fd, &header, sizeof(header));
	return (fd);
}
