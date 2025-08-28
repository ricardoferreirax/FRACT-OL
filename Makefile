# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 11:26:02 by rmedeiro          #+#    #+#              #
#    Updated: 2025/08/28 17:48:24 by rickymercur      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	fractol

HEADER = includes/fractol.h
INCLUDES = -I includes -I mlx

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

SRCS 	= 	src/fractals/burning_ship.c src/fractals/julia.c src/parsing.c src/hooks/handle_close.c \
            src/fractals/mandelbrot.c src/utils/math.c src/hooks/handle_key.c \
       		src/render.c src/hooks/handle_mouse.c src/color/update_color.c src/utils/exit.c \
			src/color/colors.c src/init_fractal.c src/utils/libft_utils.c \
			src/fractol.c \

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