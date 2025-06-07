# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 11:26:02 by rmedeiro          #+#    #+#              #
#    Updated: 2025/06/07 20:53:40 by rmedeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

NAME 	= 	fractol
SRCS 	= 	src/main.c src/fractals.c src/hooks.c \
       		src/render.c src/events.c src/utils.c \
	   		src/color.c src/init_fractal.c src/libft_utils.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -Iincludes -O2 -O3 -g3
LIBS = -Lmlx -lmlx -framework OpenGL -framework AppKit

INCLUDES = -I includes -I libft -I ft_printf -I mlx

LIBS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	make -C minilibx-linux fclean

re: fclean all

.PHONY: all clean fclean re