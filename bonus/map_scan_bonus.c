/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_scan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:26:28 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 11:40:59 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_SCAN_H
# define CUB3D_SCAN_H
# include "cub3d_bonus.h"

void		scan_file_map(t_file_sett *f, char *line, int type)
{
	if (type > 0 && g_scan_ele.count == 8)
		exit(err_handler(ERR_SPACE_EL, type, f->fd, line));
	if (g_scan_ele.count < 8)
		exit(err_handler(ERR_MISS_EL, f->n_line, f->fd, line));
	scan_map(f, line);
}

void		join_str(char **str, char *mapline)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = *str;
	tmp = ft_strjoin(*str, "|");
	*str = ft_strjoin(tmp, mapline);
	free(tmp);
	free(tmp2);
}

void		scan_map(t_file_sett *f, char *line)
{
	char	*mapline;
	int		t;
	char	*str;
	int		tmpl;

	str = ft_strdup(line);
	tmpl = f->n_line;
	while ((t = get_next_line(f->fd, &mapline)) == 1)
	{
		join_str(&str, mapline);
		if (line[0] == '\0')
			empty_line(str, line, f, mapline);
		if (mapline[0] != '\0' && is_valid_empty_line(mapline))
			continue ;
		line = mapline;
		f->n_line++;
	}
	if (t == 0)
		join_str(&str, mapline);
	check_end_of_map(str, mapline, f, line);
	stormap(str, tmpl);
}

int			is_valid_empty_line(const char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int			is_map_se(char *line, int n_line)
{
	size_t	i;
	int		ones;
	int		others;
	int		spaces;

	ones = 0;
	i = 0;
	others = 0;
	spaces = 0;
	while (line[i])
	{
		if (line[i] == '1')
			ones += 1;
		else if (line[i] == ' ')
			spaces += 1;
		else
			others += 1;
		i++;
	}
	if (others && spaces)
		exit(err_map_handler(ERR_OPEN_MAP, n_line - 1, line));
	if ((ones == 0) && (spaces == 0))
		return (0);
	return (1);
}
#endif