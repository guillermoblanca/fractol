/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:44:24 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/27 12:39:08 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"

static int	julia(double c_re, double c_im, t_fractal *fractal)
{
	int		i;
	double	old_re;
	double	old_im;
	double	new_re;
	double	new_im;

	new_re = c_re;
	new_im = c_im;
	old_re = new_re;
	old_im = new_im;
	new_re = c_re;
	new_im = c_im;
	i = 0;
	while (i++ < fractal->max_iteration)
	{
		old_re = new_re;
		old_im = new_im;
		new_re = old_re * old_re - old_im * old_im + fractal->c_re;
		new_im = 2 * old_re * old_im + fractal->c_im;
		if ((new_re * new_re + new_im * new_im) > 4)
			break ;
	}
	return (i);
}

t_fractal	*create_julia(void)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)malloc(sizeof(t_fractal));
	if (!fractal)
		return (NULL);
	fractal->zoom = 1.3;
	fractal->offset_x = -1.3;
	fractal->offset_y = -0.8;
	fractal->c_re = -0.7;
	fractal->c_im = 0.275;
	fractal->render = ft_fractal_julia;
	fractal->max_iteration = 30;
	fractal->color_func = get_palette_third;
	return (fractal);
}

void	ft_fractal_julia(void *param)
{
	t_fractal	*fractal;
	t_intvec2	vec;
	uint32_t	color;
	t_point		p;
	t_point		complex;

	fractal = (t_fractal *)param;
	p = get_zoomfactor(fractal->zoom, fractal->image->width,
			fractal->image->height);
	vec.x = 0;
	while (++vec.x < fractal->image->width)
	{
		vec.y = 0;
		while (++vec.y < fractal->image->height)
		{
			complex.x = 1.5 * vec.x / p.x + fractal->offset_x;
			complex.y = vec.y / p.y + fractal->offset_y;
			color = get_color(
					julia(complex.x, complex.y, fractal),
					fractal->max_iteration,
					fractal->color_func);
			mlx_put_pixel(fractal->image, vec.x, vec.y, color);
		}
	}
}
