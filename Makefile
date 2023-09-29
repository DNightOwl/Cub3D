# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 17:37:44 by laafilal          #+#    #+#              #
#    Updated: 2023/09/29 15:57:45 by laafilal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc

CFLAGS = -Wall -Werror -Wextra

OS := $(shell uname)



MSRC = cub3d.c


SUBSRCS = map_scan_bonus.c  map_checker_bonus.c map_storing_bonus.c \
			textures_bonus.c raycasting_bonus.c drawing_bonus.c \
			ver_intersection_bonus.c horz_intersection_bonus.c cub_file_bonus.c \
			colors_bonus.c resolution_bonus.c errors_bonus.c player_bonus.c \
			screenshot_bonus.c game_run_bonus.c sprites_bonus.c inits_bonus.c \
			utils_bonus.c cub_utils_bonus.c
MPATH = ./bonus
HEADER = cub3d_bonus.h


HEADERS = ./libft/libft.h ./get_next_line/get_next_line.h 

SUBOBJS = $(SUBSRCS:%.c=%.o)

# For an Linux and MAC_OS
ifeq ($(OS), $(filter $(OS), Linux Darwin))
	ifeq ($(OS),Linux)
		IDIR = -I./libft -I./get_next_line -I$(MPATH) -I. -I.. -I/usr/include
		LIBS = -L./libft -lft -L./get_next_line -lgnl -L./mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 
		MLX_LIB = ./mlx_linux/libmlx.a
		MLX_FOLDER = mlx_linux 
	else ifeq ($(OS),Darwin)
		IDIR = -I./libft -I./get_next_line -I./mlx -I$(MPATH) -I.  -I.. -I /usr/local/include
		LIBS = -L./libft -lft -L./get_next_line -lgnl -L /usr/lib/ -L./mlx -lmlx -framework OpenGL -framework AppKit ./mlx/libmlx.dylib
		MLX_LIB = ./mlx/libmlx.dylib
		MLX_FOLDER = mlx 
	endif
all: $(NAME)
clean:
	/bin/rm -f *.o
	cd bonus && /bin/rm -f *.o
	cd libft && $(MAKE) clean
	cd get_next_line && $(MAKE) clean
	cd $(MLX_FOLDER) && $(MAKE) clean

fclean: clean
	/bin/rm -f $(NAME)
	cd libft && $(MAKE) fclean
	cd get_next_line && $(MAKE) fclean
re: fclean libre all


# For Other OSs
else
all:
	@echo "This Project can't be run for this OS You need to run it on LINUX or MAC_OS"
re:
	@echo "This Project can't be run for this OS You need to run it on LINUX or MAC_OS"
clean :
	@echo "Nothing to be cleaned"
fclean :
	@echo "Nothing to be fcleaned"
endif


$(NAME): $(HEADER) $(addprefix $(MPATH)/,$(SUBOBJS))| ./get_next_line/libgnl.a $(MLX_LIB)
	$(CC) $(CFLAGS) $(IDIR) $(MSRC) -o $(NAME) $(addprefix $(MPATH)/,$(SUBOBJS)) $(LIBS)

$(addprefix $(MPATH)/,$(SUBOBJS)):
	cd $(MPATH) && $(CC) $(CFLAGS) -I../libft -I../get_next_line -I.. -I. -I../mlx_linux -I/usr/include -c $(SUBSRCS)

./libft/libft.a: ./libft/libft.h
	$(MAKE) -C libft

./get_next_line/libgnl.a: ./libft/libft.a ./get_next_line/get_next_line.h
	$(MAKE) -C get_next_line
	

./mlx_linux/libmlx.a: ./mlx_linux/mlx.h
	cd mlx_linux && $(MAKE)

./mlx/libmlx.dylib: ./mlx/mlx.h
	cd mlx && $(MAKE)
	install_name_tool -id ./mlx/libmlx.dylib ./mlx/libmlx.dylib

libre:
	cd libft && $(MAKE) re
	cd get_next_line && $(MAKE) re
