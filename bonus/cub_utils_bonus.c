/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:10:59 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/05 11:06:55 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_UTILS_H
# define CUB3D_UTILS_H
# include "cub3d_bonus.h"

double		distance(double x, double y)
{
	double	dis;

	dis = (x - g_player.x) * (x - g_player.x)
		+ (y - g_player.y) * (y - g_player.y);
	dis = sqrtf(dis);
	return (dis);
}

void		norm_in_pi_range(double *angle)
{
	if (*angle > M_PI)
		*angle -= M_PI * 2;
	if (*angle < -M_PI)
		*angle += M_PI * 2;
	*angle = fabs(*angle);
}

double		angle_norme(double angle)
{
	double angl;

	angl = fmod(angle * 180 / M_PI, 360);
	if (angl < 0)
		angl = 360 + angl;
	return (angl);
}

double		radian_norme(double radian)
{
	double rad;

	rad = fmodf(radian, 2 * M_PI);
	if (rad < 0)
		rad = 2 * M_PI + rad;
	return (rad);
}

void		free_all(char **t)
{
	int		i;

	i = 0;
	while (t[i])
		free(t[i++]);
	free(t);
}

#endif