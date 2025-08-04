# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 11:26:02 by rmedeiro          #+#    #+#              #
#    Updated: 2025/08/04 16:45:06 by rmedeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	fractol

HEADER = includes/fractol.h
INCLUDES = -I includes -I mlx

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

CFLAGS = -Wall -Wextra -Werror -g3
LFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

SRCS 	= 	src/fractals/burning_ship.c src/fractals/julia.c src/parsing.c \
            src/fractals/mandelbrot.c src/fractals/phoenix.c src/math.c \
       		src/render.c src/events.c src/color_utils.c src/exit.c src/fractol_linux.c \
	   		src/color.c src/init_fractal.c src/libft_utils.c src/fractol.c \

OBJS = $(SRCS:.c=.o)

REPO := https://github.com/42paris/minilibx-linux.git

RED = \033[1;30;41m
GREEN = \033[1;30;42m
OFF := \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
		$(MAKE) -C $(MLX_DIR)
		@echo "$(GREEN) Minilibix Compiled $(OFF)"
		$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
		@echo "$(GREEN) Fractol Created $(OFF)"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

mlx:
	git clone $(REPO)

clean:
	rm -f $(OBJS)
	@echo "$(RED) Delete Obj Files $(OFF)"

fclean: clean
	rm -f $(NAME)
	@echo "$(RED) Delete Fractol exe $(OFF)"

re: fclean all

del: fclean
	rm -rf $(MLX_DIR)
	@echo "$(RED) Minilibx Deleted $(OFF)"

.PHONY: all clean fclean re