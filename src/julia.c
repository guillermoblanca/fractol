/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:44:24 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/23 14:44:27 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"

static int	julia(double newRe, double newIm, double cRe, double cIm, int max_iteration)
{
	int		i;
	double	old_re;
	double	old_im;

	old_re = newRe;
	old_im = newIm;
	i = 0;
	while (i++ < max_iteration)
	{
		old_re = newRe;
		old_im = newIm;
		newRe = old_re * old_re - old_im * old_im + cRe;
		newIm = 2 * old_re * old_im + cIm;
		if ((newRe * newRe + newIm * newIm) > 4)
			break ;
	}
	return (i);
}

t_fractal	*create_julia(void)
{
	t_fractal	*fractal;

	fractal = malloc(sizeof(t_fractal));
	if (!fractal)
		return (NULL);
	fractal->zoom = 1.3;
	fractal->offset_x = -1.3;
	fractal->offset_y = -0.8;
	fractal->c_re = -0.7;
	fractal->c_im = 0.27015;
	fractal->render = ft_fractal_julia;
	fractal->width = 1.9;
	fractal->height = 0.23;
	fractal->max_iteration = 30;
	fractal->color_func = get_palette_third;
	return (fractal);
}


void ft_fractal_julia(void* param) {
	t_fractal* fractal = (t_fractal*)param;
	uint32_t x, y;
	t_point p;

	p = get_zoomfactor(fractal->zoom, fractal->image->width, fractal->image->height);
	for (x = 0; x < fractal->image->width; x++) {
		for (y = 0; y < fractal->image->height; y++) {
			double newRe = 1.5 * x / p.x + fractal->offset_x;
			double newIm = y / p.y + fractal->offset_y;
			uint32_t color = get_color(
				julia(newRe, newIm, fractal->c_re, fractal->c_im, fractal->max_iteration), 
			fractal->max_iteration,
			 fractal->color_func);
			mlx_put_pixel(fractal->image, x, y, color);
		}
	}
}