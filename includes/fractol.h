/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:32:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/13 09:27:41 by rmedeiro         ###   ########.fr       */
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

# define PI2 6.28318530
# define PI 3.141592653

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

typedef struct s_fractal
{
	void	*mlx;
	void	*win;
	void	*img;
	int		res_height;
	int		res_width;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		type;
	double	zoom;
	double	offset_x;
	double	offset_y;
	int		max_iter;
	double	julia_re;
	double	julia_im;
	int		color_scheme;
}	t_fractal;

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
