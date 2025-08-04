/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:32:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/04 15:14:49 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800

/* Misc */
# define MAX_ITER 50
# define ITER_TRESHOLD 310

/* Err Codes */
# define QUIT 0
# define INPUT 1
# define MALLOC 2

/* Libraries */
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

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

int			julia(t_complex z, t_complex c, int max_iter);
int			mandelbrot(t_complex c, int max_iter);
int			burning_ship(t_complex c, int max_iter);
void		init_graphics(t_fractal *fractal);
void		init_fractal_type(t_fractal *fractal, int argc, char **argv);
void		init_fractal(t_fractal *fractal, int argc, char **argv);
int			validate_args(int argc, char **argv);
void		put_pixel(t_fractal *fractal, int x, int y, int color);
t_complex	compute_complex(int x, int y, t_fractal *fractal);
int			compute_iteration(t_complex c, t_fractal *fractal);
void		render_fractal(t_fractal *fractal);
int			handle_key(int keycode, t_fractal *fractal);
int			handle_mouse(int button, int x, int y, t_fractal *fractal);
int			close_win(t_fractal *fractal);
int			coloring(double i, t_fractal *fractal);
int			bernstein_polynomials(double i, int version, int max_iter);
int			cosine_coloring(double i, int version, int max_iter);
int			color_rainbow(double i, int max_iter);
int			get_colors(double i, t_fractal *fractal);
double		interpolation(double i, double min, double max, int max_iter);
void		normalize_color_scheme(t_fractal *fractal);
void		print_usage(void);
void		free_fractal(t_fractal *fractal);
void		*ft_memset(void *s, int c, size_t n);
int			ft_strcmp(char *s1, char *s2);
void		ft_putstr(char *s);
double		ft_atof(char *str);

#endif
