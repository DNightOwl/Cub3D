/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:47:46 by laafilal          #+#    #+#             */
/*   Updated: 2020/12/08 20:10:44 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int		end_line(char *buff)
{
	int		i;

	i = 0;
	while (buff[i] != '\n')
		i++;
	return (i);
}

static	void	line_join(char **line, char *buff)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(tmp, buff);
	free(tmp);
}

static	void	split_end_line(char **line, char *buff)
{
	int		idx;
	char	*s;

	idx = end_line(buff);
	s = ft_substr(buff, 0, idx);
	line_join(line, s);
	free(s);
	s = ft_substr(buff, idx + 1, BUFFER_SIZE);
	strncpy(buff, s, BUFFER_SIZE);
	free(s);
}

int				get_next_line(int fd, char **line)
{
	static	char	buff[BUFFER_SIZE + 1] = "";
	int				t;

	if (!line || !(*line = ft_strdup("")))
		return (-1);
	if (!ft_strchr(buff, '\n') && ft_strlen(buff) != 0)
		line_join(line, buff);
	while (!ft_strchr(buff, '\n'))
	{
		if ((t = read(fd, &buff, BUFFER_SIZE)) > 0)
		{
			buff[t] = '\0';
			if (!ft_strchr(buff, '\n'))
				line_join(line, buff);
		}
		else
		{
			buff[0] = '\0';
			return (t);
		}
	}
	if (ft_strchr(buff, '\n'))
		split_end_line(line, buff);
	return (1);
}
