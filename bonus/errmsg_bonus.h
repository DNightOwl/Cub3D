/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 19:15:33 by laafilal          #+#    #+#             */
/*   Updated: 2021/03/06 16:38:26 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRMSG_BONUS_H
# define ERRMSG_BONUS_H
# define ERR_NULL_ARGS 0
# define ERR_LOT_ARGS 1
# define ERR_SND_ARG 2
# define ERR_FRS_ARG 3
# define ERR_SPACE_EL 4
# define ERR_NO_EL 5
# define ERR_DUP_EL 6
# define ERR_MISS_EL 7
# define ERR_WRONG_EL 8
# define ERR_MISS_INF 9
# define ERR_FAILED 10
# define ERR_R_INF 11
# define ERR_DIG_INF 12
# define ERR_INIT_FAIL 13
# define ERR_XPM 14
# define ERR_MIN_R 15
# define ERR_SPACE_INF 16
# define ERR_ONE_PATH 17
# define ERR_COMA_COL 18
# define ERR_PARAM_COL 19
# define ERR_DIGIT_COL 20
# define ERR_EL 21
# define ERR_MISS_MAP 22
# define ERR_E_LINE_MAP 23
# define ERR_E_LAST_MAP 24
# define ERR_NO_PLAYER 25
# define ERR_DUP_PLAYER 26
# define ERR_OPEN_MAP 27
# define ERR_LAST_MAP 28
# define ERR_EL_MAP 29


typedef struct		s_errormsgs
{
	int		code;
	char	*message;
}					t_errormsgs;

// static t_errormsgs			g_errormsgs[30] = {
// 	{ ERR_NULL_ARGS, "Needs at least one argument !" },
// 	{ ERR_LOT_ARGS, "Too much arguments !" },
// 	{ ERR_SND_ARG, "The second argument is wrong !" },
// 	{ ERR_FRS_ARG, "The Fisrt argument is wrong !" },
// 	{ ERR_SPACE_EL, "An element starts or ends with a white space !" },
// 	{ ERR_NO_EL, "No element specified  R|NO|SO|WE|EA|S|F|C" },
// 	{ ERR_DUP_EL, "There is a duplicated element !" },
// 	{ ERR_MISS_EL, "There is a missing element before the map !" },
// 	{ ERR_WRONG_EL, "Wrong identifier !" },
// 	{ ERR_MISS_INF, "Informations are missing for this identifier !" },
// 	{ ERR_FAILED, "Execution failed!" },
// 	{ ERR_R_INF, "Resolution need only 2 informations!" },
// 	{ ERR_DIG_INF, "Resolution's informations should be a positive digits !" },
// 	{ ERR_INIT_FAIL, "the mlx init failed !" },
// 	{ ERR_XPM, "faild to read the xpm file, is missing or wrong path !" },
// 	{ ERR_MIN_R, "the min resolution should be 50 by 50" },
// 	{ ERR_SPACE_INF, "information can only be seprated by space/multispaces" },
// 	{ ERR_ONE_PATH, "needs only one information : the path of xpm file" },
// 	{ ERR_COMA_COL, "cant be separated by white spaces, use only a coma" },
// 	{ ERR_PARAM_COL, "support one information of 3 colors R,G,B" },
// 	{ ERR_DIGIT_COL, "must be 3 digits in range of [0,255]" },
// 	{ ERR_EL, "unvalid element" },
// 	{ ERR_MISS_MAP, "map is missing" },
// 	{ ERR_E_LINE_MAP, "The map shoundnt be separated by emty lines" },
// 	{ ERR_E_LAST_MAP, "The map shoundnt end with an emty line" },
// 	{ ERR_NO_PLAYER, "The player is missing" },
// 	{ ERR_DUP_PLAYER, "There are more than one player" },
// 	{ ERR_OPEN_MAP, "The map is not closed" },
// 	{ ERR_LAST_MAP, "Invalid element ,the map should be the last in file" },
// 	{ ERR_EL_MAP, "unvalid element for the map" },
// };

// # define ERR_NULL_ARGS1 "Needs at least one argument !"
// # define ERR_LOT_ARGS2 "Too much arguments !"

#endif
