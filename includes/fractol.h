/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:32:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/27 19:03:38 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 800

# define MAX_ITER 50
# define ITER_TRESHOLD 310

# define QUIT 0
# define INPUT 1
# define MALLOC 2
# define MLX_FAIL 3

# define KEY_RED_CROSS 17
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_MINUS 45
# define KEY_PLUS 61
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define KEY_C 99
# define KEY_H 104
# define KEY_B 98
# define KEY_M 109
# define KEY_J 106
# define KEY_P 112
# define KEY_I 105
# define KEY_R 114
# define KEY_O 111

/* Cleanup Linux */
#ifdef __linux__
void fractol_linux_cleanup(void *mlx);
#else
static inline void fractol_linux_cleanup(void *mlx)
{
    (void)mlx; // função vazia em outras plataformas
}
#endif

# define BLACK   0xFF000000

typedef struct s_pixel
{
	double	x;
	double	y;
}			t_pixel;

typedef struct s_complex
{
	double	re;
	double	im;
}			t_complex;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_fractol
{
	void		*mlx;
	void		*win;
	t_img		img;
	char		*type;
	int			c_max_iter;
	int			color_mode;
	int			*color_table;
	double		zoom;
	double		offset_x;
	double		offset_y;
	double		julia_re;
	double		julia_im;
}				t_fractol;

/* Maths */
t_complex	c_add(t_complex a, t_complex b);
t_complex	c_mult(t_complex a, t_complex b);
double	    ft_abs(double x);
double		scale(double to_scale, double n_min, double n_max, double o_max);

/* Init */
void	    init_defaults(t_fractol *f);
void		init_fractol(t_fractol *f);

/* Fractals */
int			mandelbrot(t_complex c, int c_max_iter);
int			julia(t_complex c, t_complex z, int c_max_iter);
int			burning_ship(t_complex c, int c_max_iter);

void	    set_default_julia(t_fractol *f);

/* Palettes */
int			polynomial_gradient(int iter, int max_iter);
int	        sin_gradient(int iter, int max_iter);
int			flame_gradient(int iter, int max_iter);
int         ocean_gradient(int iter, int max_iter);

int			colorize(int nb_iter, t_fractol *f);
void		update_color(t_fractol *f);

void		init_image(t_fractol *f);
t_complex	ft_mapping(int x, int y, t_fractol *f);
void		render_fractal(t_fractol *f);
void		exit_fractol(int errcode, t_fractol *f);
void        free_fractol(t_fractol *f);
void	    my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			fractal_escape_time(t_fractol *f, t_complex *c_point);

int		    handle_close(void *param);
int	        handle_key(int keycode, void *param);
int		    handle_mouse_key(int keycode, int x, int y, void *param);

void	    check_input(t_fractol *f, int ac, char **av);
double	    ft_atof(const char *str);

void	    ft_putstr(char *s);
int	        ft_strcmp(const char *s1, const char *s2);

#endif
