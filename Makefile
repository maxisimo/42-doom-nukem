# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/01 00:25:16 by thbernar          #+#    #+#              #
#    Updated: 2019/01/14 15:52:23 by maxisimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

NAME_MAP = map-generator

SRC = main.c \
	  utils.c \
	  utils2.c \
	  info.c \
	  raycasting.c \
	  app.c \
	  minimap.c \
	  key_hook.c \
	  mouse_hook.c \
	  doors.c \
	  draw.c \
	  move.c \
	  weapons.c \
	  sprites.c \
	  load.c \
	  shades.c \
	  screens.c \
	  posters.c \
	  enemies.c \
	  enemies_init.c \
	  bmp_parser.c

SRC_MAP = map_generator/main.c \
	  map_generator/utils.c \
	  map_generator/draw.c \
	  map_generator/hook.c \
	  map_generator/editor.c \
	  bmp_parser.c \
	  utils.c \
	  utils2.c \
	  minimap.c \
	  shades.c \
	  doors.c \
	  screens.c \
	  posters.c

OBJ = $(SRC:%.c=%.o)

OBJ_MAP = $(SRC_MAP:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBMLX := -Lminilibx -lmlx
LIBFT := -Llibft -lft

LFT := libft/libft.a
LMLX := minilibx/libmlx.a

FRAMEWORK := -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME) : $(OBJ) $(LFT) $(LMLX)
	$(CC) $(CFLAGS) $(LIBMLX) $(LIBFT) $(FRAMEWORK) $(OBJ) -o $(NAME)

$(NAME_MAP) : $(OBJ_MAP) $(LFT) $(LMLX)
	$(CC) $(CFLAGS) $(LIBMLX) $(LIBFT) $(FRAMEWORK) $(OBJ_MAP) -o $(NAME_MAP)

libft/libft.a:
	make -C libft

minilibx/libmlx.a:
	make -C minilibx

clean:
	make clean -C libft
	make clean -C minilibx
	rm -rf $(OBJ) $(OBJ_MAP)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME) $(NAME_MAP)

re : fclean all
