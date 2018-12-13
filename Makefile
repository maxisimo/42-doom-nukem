# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/01 00:25:16 by thbernar          #+#    #+#              #
#    Updated: 2018/12/13 18:15:07 by maxisimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

SRC = main.c \
	  fts_utils.c \
	  fts_utils2.c \
	  fts_raycasting.c \
	  fts_app.c \
	  fts_minimap.c \
	  fts_hook.c \
	  fts_draw.c \
	  fts_move.c \
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
