/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:44:34 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/27 11:40:54 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTALS_H
# define FRACTALS_H
# include "../inc/mlx42/include/MLX42/MLX42.h"
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# define WIDTH 1024
# define HEIGHT 720
# define HEX "0123456789ABCDEF"

typedef struct s_color
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
}	t_color;

typedef void	(*t_render_func)(void*);
typedef t_color	(*t_color_func)(int);

typedef struct s_fractal
{
	mlx_image_t		*image;
	mlx_t			*mlx;
	int32_t			width;
	int32_t			height;
	double			zoom;
	double			offset_x;
	double			offset_y;
	double			c_re;
	double			c_im;
	int				max_iteration;
	t_render_func	render;
	t_color_func	color_func;
}	t_fractal;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_intvec2
{
	uint32_t	x;
	uint32_t	y;
}	t_intvec2;

t_point		get_zoomfactor(double zoom, double imageW, double imageH);
//////////////////////////////////////////////////////
//
//						FRACTALS
//
//////////////////////////////////////////////////////

t_fractal	*create_julia(void);
void		ft_fractal_julia(void *param);
t_fractal	*create_mandelbrot(void);
void		ft_fractal_mandelbrot(void *param);
t_fractal	*create_william(void);
void		ft_fractal_william(void *param);
//////////////////////////////////////////////////////
//
//						EVENTS
//
//////////////////////////////////////////////////////

void		ft_bindevents(void *param);
void		ft_hook(void *param);
void		ft_scroll(double xdelta, double ydelta, void *param);
void		ft_close(void *param);
void		ft_fractal_error(void);

//////////////////////////////////////////////////////
//
//						COLOR
//
//////////////////////////////////////////////////////

int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
uint32_t	get_color(int iter, int max_iter, t_color_func func);
t_color		hex_to_color(const char *hex);
t_color		get_palette_pimary(int iteration);
t_color		get_palette_secondary(int iteration);
t_color		get_palette_third(int iteration);
t_color		lerp_color(t_color a, t_color b, float delta);
int			lerp(int min, int max, float delta);

//////////////////////////////////////////////////////
//
//						INSTRUCTIONS
//
//////////////////////////////////////////////////////
void		print_instructions(void);
void		print_algorithms(void);
//////////////////////////////////////////////////////
//
//						LIBFT
//
//////////////////////////////////////////////////////
int			ft_strncmp(const char *s1, const char *s2, size_t n);
#endif