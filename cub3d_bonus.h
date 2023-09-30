/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 18:56:30 by laafilal          #+#    #+#             */
/*   Updated: 2023/09/29 15:53:38 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# include <errmsg_bonus.h>
# ifdef __linux__
#  include <X11/Xlib.h>
#  include <X11/X.h>
# endif
# include <libft.h>
# include <get_next_line.h>
# include <mlx.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>

# define KEYPRESS        2
# define KEYRELEASE      3
# define DESTROYNOTIFY       17
# define MAX_NUM 2147483647
# define SCREENSHOT_NAME "screenshot.bmp"
# define TILE_SIZE 64
# define WIN_TITLE "cub3D"
# define SHADE_RANGE 2000

# if defined(__linux__)
#  define WALK 119
#  define BACK 115
#  define RIGHT 100
#  define LEFT 97
#  define TURNLEFT 65361
#  define TURNRIGHT 65363
#  define ESC 65307
# else
#  define WALK 13
#  define BACK 1
#  define RIGHT 2
#  define LEFT 0
#  define TURNLEFT 123
#  define TURNRIGHT 124
#  define ESC 53
# endif




typedef struct	s_file_sett {
	int			fd;
	char		*line;
	int			n_line;
}				t_file_sett;

/*
** map info
*/
typedef struct	s_map_data {
	int			nb_rows;
	int			nb_cols;
	int			width;
	int			height;
	char		**map;
}				t_map_data;

typedef struct	s_player {
	double		x;
	double		y;
	double		radius;
	int			turndirection;
	int			walkdirection;
	double		walkside;
	double		rotationangle;
	double		movespeed;
	double		rotationspeed;
}				t_player;

typedef struct	s_ray {
	double		rayangle;
	double		wallhit_x;
	double		wallhit_y;
	double		distance;
	int			was_hit_vert;
	int			look_up;
	int			look_left;
}				t_ray;

typedef struct	s_scan_ele
{
	int			r;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			s;
	int			f;
	int			c;
	int			map;
	int			sprites;
	int			count;
}				t_scan_ele;

typedef struct	s_img_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

typedef struct	s_textures {
	t_img_data	img_n;
	t_img_data	img_s;
	t_img_data	img_w;
	t_img_data	img_e;
	t_img_data	img_sp;
	int			width;
	int			height;
	char		*n;
	char		*s;
	char		*w;
	char		*e;
	char		*sp;
}				t_textures;

typedef struct	s_wall_settings {
	double		corr_dist;
	double		dis_plane;
	double		wall_strip_hight;
	double		startx;
	double		starty;
	double		endy;
	double		cof_dist_top;
	double		rayangle;
}				t_wall_sett;

typedef struct	s_game_data {
	void		*mlx_ptr;
	void		*mlx_win;
	int			r_width;
	int			r_height;
	int			wall_strip_width;
	int			bits_per_pixel_8;
	int			plane_shade;
	int			ceilling_color;
	int			floor_color;
	int			min_res;
}				t_game_data;

typedef struct	s_sprite {
	double		x;
	double		y;
	double		dist;
	int			visible;
	double		angle;
}				t_sprite;

typedef struct	s_map_vars {
	char		grid;
	char		next_grid;
	char		*xline;
}				t_map_vars;

typedef struct	s_hit_vars {
	double		xstep;
	double		ystep;
	double		xintercept;
	double		yintercept;
}				t_hit;

typedef struct	s_wall_hit {
	int			is_wall_hit;
	double		wall_hit_x;
	double		wall_hit_y;
	double		hit_dis;
}				t_wall_hit;

typedef struct	s_sprite_sett {
	double		corr_distance;
	double		sprite_height;
	double		sprite_width;
	double		sprite_top_y;
	double		sprite_bott_y;
	double		sprite_x;
	double		sprite_left_x;
	double		sprite_right_x;
	double		angle_sp;
	double		dist_from_top;
	double		text_width;
	int			text_offset_y;
	int			text_offset_x;
	double		d;
}				t_sprite_sett;

extern t_img_data		g_img;
extern t_img_data		g_hud;
extern t_player			g_player;
extern t_scan_ele		g_scan_ele;
extern t_map_data		g_map_data;
extern t_game_data		g_game;
extern t_textures		g_texture;
extern int				g_save;
extern double			g_fov_angle;
extern int				g_num_rays;
extern double			**g_rays;

void			init_ele(void);
int				check_dup_ele(void);
int				ft_str_isdigit(const char *s);
int				ft_isspace(char c);
char			*ft_strtolower(const char *s);
int				extension_checker(const char *file_name, const char *ext);

int				err_handler(size_t err_type, int n_line, int fd, char *line);
int				err_arg_handler(size_t err_type);
int				err_conf_handler(size_t err_type, int n_line,
		int fd, char *line);
int				err_map_handler(size_t err_type, int n_line, char *line);

void			scan_file_map(t_file_sett *f, char *line, int type);
void			scan_map(t_file_sett *f, char *line);
int				is_valid_empty_line(const char *line);
int				is_map_se(char *line, int n_line);

void			free_all(char **t);
int				skipe_zeros(char *str);
int				check_min_max_res_width(char **info, int i,
		t_file_sett *f, char *line);
int				check_min_max_res_height(char **info, int j,
		t_file_sett *f, char *line);
int				overflow_res(char **info, t_file_sett *f, char *line);
void			check_res(char *inf, t_file_sett *f, char *line);
char			*check_path(char *path, t_file_sett *f, char *line);
void			empty_line(char *str, char *line, t_file_sett *f,
		char *mapline);
void			check_color(char *param, int *color,
		t_file_sett *f, char *line);
void			is_count_colors(char *param, t_file_sett *f, char *line);
int				get_color(char *param, t_file_sett *f, char *line);
void			check_first_last_line(char **map, int row_l, int n_line);
void			dup_player(char *t, char **map, int n_line, int player);
void			where_to_look(char ps);
int				map_line_elements(char *t, int y, char **map, int *player);
void			check_map_ele(char **map, int row_l, int n_line, int *player);
void			map_closed_inside(t_map_vars *v_map, char xline,
		char **map, int n_line);
void			check_map(char **map, int row_l, int n_line);
void			map_justification(char ***map_org, size_t m_l);
void			stormap(char *str, int n_line);
void			check_end_of_map(char *str, char *mapline,
		t_file_sett *f, char *line);
void			check_elements(t_file_sett *f, char *line);
void			scan_file_el(t_file_sett *f, char *line, int type);
void			scan_file_cub(t_file_sett *f);
void			file_checker_cub(char **args);

int				create_trgb(int t, int r, int g, int b);

void			textures_loader(void);
void			get_textures(t_img_data *img_t, t_ray ray);

void			cast_ray(t_ray *ray);
void			cast_all_rays(void);

void			my_mlx_pixel_put(t_img_data *img_data, int x, int y, int color);
void			draw_floor(int col, double start, double end, int color);
void			draw_ceilling(int col, double start, double end, int color);
void			draw_strip(t_ray ray, t_wall_sett wall,
		t_img_data img_t, int *t_color);

double			radian_norme(double radian);
double			angle_norme(double angle);
void			norm_in_pi_range(double *angle);
double			distance(double x, double y);

void			init_ray(t_ray *ray, double *rayangle);
void			setting_wall_var(int col, t_wall_sett *wall, t_ray ray);
void			init_sprites_sett(t_sprite_sett *sp, t_sprite visible_s);
void			textures_init_addrs(void);

void			get_sprites(t_sprite *sprites);
void			sort_sprites(int nb, t_sprite *visible);
void			render_sprite(t_sprite_sett *sp, t_sprite visible_s);
void			render_visible_sprites(int j, t_sprite *visible);
void			draw_sprites(t_sprite *sprites);

int				key_released(int keycode);
int				key_pressed(int keycode);
int				close_win(int keycode);
int				update_game(t_sprite *sprites);
void			game_run(void);

int				write_screenshot_header(void);
void			game_save(void);

void			init_player(void);
void			dup_player(char *t, char **map, int n_line, int player);
void			where_to_look(char ps);

int				color_shade(double dist, int color, int shade_range);

void			v_intercepts(t_hit *hit, double x, double y, double *rayangle);
void			v_cal_steps(t_hit *hit, double rayangle);
int				get_next_ver_hit(t_hit *hit, t_ray *ray, double *v_wall_hit_x,
		double *v_wall_hit_y);
int				vertical_intersection(t_ray *ray, double *v_wall_hit_x,
		double *v_wall_hit_y);

void			h_intercepts(t_hit *hit, double x, double y, double *rayangle);
void			h_cal_steps(t_hit *hit, double rayangle);
int				get_next_hor_hit(t_hit *hit, t_ray *ray,
		double *h_wall_hit_x, double *h_wall_hit_y);
int				horizontal_intersection(t_ray *ray, double *h_wall_hit_x,
		double *h_wall_hit_y);

void			init_game(void);
int				is_wall(double nx, double ny);

void			player_exist(int player, char **map, int n_line);
void			object_collision(double new_px, double new_py);
void		put_sprite_pixel(t_sprite_sett *sp,int x, int y, int *t_color);
#endif
