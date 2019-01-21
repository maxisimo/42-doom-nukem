# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/01 00:25:16 by thbernar          #+#    #+#              #
#    Updated: 2019/01/16 18:02:02 by lchappon         ###   ########.fr        #
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

.PHONY: all clean fclean doom_clean map_clean doom_fclean map_fclean doom_re map_re

all: $(NAME) $(NAME_MAP)

$(NAME) : $(OBJ) $(LFT) $(LMLX)
	$(CC) $(CFLAGS) $(LIBMLX) $(LIBFT) $(FRAMEWORK) $(OBJ) -o $(NAME)

$(NAME_MAP) : $(OBJ_MAP) $(LFT) $(LMLX)
	$(CC) $(CFLAGS) $(LIBMLX) $(LIBFT) $(FRAMEWORK) $(OBJ_MAP) -o $(NAME_MAP)

libft/libft.a:
	make -C libft

minilibx/libmlx.a:
	make -C minilibx

doom_clean:
	make clean -C libft
	make clean -C minilibx
	rm -rf $(OBJ)

map_clean:
	make clean -C libft
	make clean -C minilibx
	rm -rf $(OBJ_MAP)

clean:
	make clean -C libft
	make clean -C minilibx
	rm -rf $(OBJ) $(OBJ_MAP)

doom_fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

map_fclean: clean
	make fclean -C libft
	rm -rf $(NAME_MAP)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME) $(NAME_MAP)

doom_re : doom_fclean $(NAME)

map_re : map_fclean $(NAME_MAP)

re : fclean all
