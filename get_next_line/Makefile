# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/08 19:38:46 by laafilal          #+#    #+#              #
#    Updated: 2020/12/14 21:04:04 by laafilal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIB_PATH = ../libft

IDIR = -I$(LIB_PATH)

MSRC = get_next_line.c

MOBJ = $(MSRC:%.c=%.o)

HEADERS = get_next_line.h $(LIB_PATH)/libft.h

all: $(NAME)

$(NAME): $(MOBJ)
	ar rcs $(NAME) $(MOBJ)

$(MOBJ): $(HEADERS)
	$(CC) $(CFLAGS) -c $(IDIR)  $(MSRC) 

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
