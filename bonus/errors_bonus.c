/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:12:51 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/05 11:38:44 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_errormsgs			g_errormsgs[30] = {
	{ ERR_NULL_ARGS, "Needs at least one argument !" },
	{ ERR_LOT_ARGS, "Too much arguments !" },
	{ ERR_SND_ARG, "The second argument is wrong !" },
	{ ERR_FRS_ARG, "The Fisrt argument is wrong !" },
	{ ERR_SPACE_EL, "An element starts or ends with a white space !" },
	{ ERR_NO_EL, "No element specified  R|NO|SO|WE|EA|S|F|C" },
	{ ERR_DUP_EL, "There is a duplicated element !" },
	{ ERR_MISS_EL, "There is a missing element before the map !" },
	{ ERR_WRONG_EL, "Wrong identifier !" },
	{ ERR_MISS_INF, "Informations are missing for this identifier !" },
	{ ERR_FAILED, "Execution failed!" },
	{ ERR_R_INF, "Resolution need only 2 informations!" },
	{ ERR_DIG_INF, "Resolution's informations should be a positive digits !" },
	{ ERR_INIT_FAIL, "the mlx init failed !" },
	{ ERR_XPM, "faild to read the xpm file, is missing or wrong path !" },
	{ ERR_MIN_R, "the min resolution should be 50 by 50" },
	{ ERR_SPACE_INF, "information can only be seprated by space/multispaces" },
	{ ERR_ONE_PATH, "needs only one information : the path of xpm file" },
	{ ERR_COMA_COL, "cant be separated by white spaces, use only a coma" },
	{ ERR_PARAM_COL, "support one information of 3 colors R,G,B" },
	{ ERR_DIGIT_COL, "must be 3 digits in range of [0,255]" },
	{ ERR_EL, "unvalid element" },
	{ ERR_MISS_MAP, "map is missing" },
	{ ERR_E_LINE_MAP, "The map shoundnt be separated by emty lines" },
	{ ERR_E_LAST_MAP, "The map shoundnt end with an emty line" },
	{ ERR_NO_PLAYER, "The player is missing" },
	{ ERR_DUP_PLAYER, "There are more than one player" },
	{ ERR_OPEN_MAP, "The map is not closed" },
	{ ERR_LAST_MAP, "Invalid element ,the map should be the last in file" },
	{ ERR_EL_MAP, "unvalid element for the map" },
};

int			err_handler(size_t err_type, int n_line, int fd, char *line)
{
	ft_putstr_fd("Error\n", 2);
	if (err_type <= 3)
	{
		close(fd);
		return (err_arg_handler(err_type));
	}
	if (err_type > 3 && err_type <= 21)
		return (err_conf_handler(err_type, n_line, fd, line));
	else
		return (err_map_handler(err_type, n_line, line));
	return (0);
}

int			err_conf_handler(size_t err_type, int n_line, int fd, char *line)
{
	close(fd);
	ft_putstr_fd("line[", 2);
	ft_putnbr_fd(n_line, 2);
	ft_putstr_fd("] : ", 2);
	ft_putstr_fd(g_errormsgs[err_type].message, 2);
	free(line);
	return (1);
}

int			err_arg_handler(size_t err_type)
{
	ft_putstr_fd(g_errormsgs[err_type].message, 2);
	ft_putstr_fd("\n<cub3D [file.cub] [--save]>\n", 2);
	return (1);
}

int			err_map_handler(size_t err_type, int n_line, char *line)
{
	ft_putstr_fd("line[", 2);
	ft_putnbr_fd(n_line, 2);
	ft_putstr_fd("] : ", 2);
	ft_putstr_fd(g_errormsgs[err_type].message, 2);
	free(line);
	return (1);
}
