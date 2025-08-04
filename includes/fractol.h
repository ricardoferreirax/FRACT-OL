/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:32:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/04 21:51:05 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 800

/* Misc */
# define MAX_ITER 50
# define ITER_TRESHOLD 310

/* Err Codes */
# define QUIT 0
# define INPUT 1
# define MALLOC 2

/* KEYS */
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

/* Cleanup Linux */
#ifdef __linux__
void fractol_linux_cleanup(void *mlx);
#else
static inline void fractol_linux_cleanup(void *mlx)
{
    (void)mlx; // função vazia em outras plataformas
}
#endif

/* COLORS */
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

typedef struct s_phoenix
{
	t_complex	p;
	t_complex	c;
}				t_phoenix;

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
	t_phoenix	pv;
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
int			phoenix(t_complex z, t_complex k, t_complex c, int c_max_iter);

/* Palettes */
int			poli_gradiant(int iter, int max_iter);
int			sin_tripy(int iter, int max_iter);
int			fire_thing(int iter, int max_iter);
int			purple_trip(int iter, int max_iter);

int			colorize(int nb_iter, t_fractol *f);
void		update_color_table(t_fractol *f);

void		init_image(t_fractol *f);
void		render_fractal(t_fractol *f);
void		exit_fractol(int errcode, t_fractol *f);
void        free_fractol(t_fractol *f);
void	    my_mlx_pixel_put(t_img *img, int x, int y, int color);
int	        get_fractal_iterations(t_fractol *f, t_complex *p);

void		handle_close(t_fractol *f);
void		handle_key(int keycode, t_fractol *f);
void		handle_mouse_key(int keycode, int x, int y, t_fractol *f);

void	    check_input(t_fractol *f, int ac, char **av);
double	    ft_atof(const char *str);

void	    ft_putstr(char *s);
int	        ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
