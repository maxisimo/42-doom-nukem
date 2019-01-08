# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 22:26:16 by maxisimo          #+#    #+#              #
#    Updated: 2019/01/07 20:45:28 by maxisimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = map_generator

SRC = main.c \
	  map_generator.c \
	  utils.c \
	  draw.c \
	  hook.c \
	  color.c \
	  ../bmp_parser.c \
	  ../utils.c \
	  ../utils2.c \
	  ../minimap.c \
	  ../shades.c \
	  ../doors.c \
	  ../screens.c \
	  ../posters.c \
	  editor.c

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
