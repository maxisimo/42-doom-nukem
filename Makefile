# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/01 00:25:16 by thbernar          #+#    #+#              #
#    Updated: 2018/12/16 16:09:50 by lchappon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

SRC = main.c \
	  utils.c \
	  utils2.c \
	  raycasting.c \
	  app.c \
	  minimap.c \
	  hook.c \
	  draw.c \
	  move.c \
	  weapons.c \
	  sprites.c \
	  textures.c \
	  shades.c \
	  startscreen.c \
	  enemies.c \
	  bmp_parser.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBMLX := -Lminilibx -lmlx
LIBFT := -Llibft -lft

LFT := libft/libft.a

FRAMEWORK := -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME) : $(OBJ) libft/libft.a minilibx/libmlx.a
	$(CC) $(CFLAGS) $(LIBMLX) $(LIBFT) $(FRAMEWORK) $(OBJ) -o $(NAME)

libft/libft.a:
	make -C libft

minilibx/libmlx.a:
	make -C minilibx

clean:
	make clean -C libft
	make clean -C minilibx
	rm -rf $(OBJ)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re : fclean all
