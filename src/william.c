/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   william.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:44:53 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/27 13:16:15 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"
#include <math.h>

static int	william(t_point complex, double re, double im, int max_iteration)
{
	int		i;
	t_point	newp;
	t_point	oldp;

	i = 0;
	newp.x = re;
	newp.y = im;
	while (i++ < max_iteration)
	{
		oldp.x = newp.x;
		oldp.y = newp.y;
		newp.x = fabs(oldp.x * oldp.x - oldp.y * oldp.y + complex.x);
		newp.y = 2 * oldp.x * oldp.y + complex.y;
		if ((newp.x * newp.x + newp.y * newp.y) > 4)
			break ;
	}
	return (i);
}

t_fractal	*create_william(void)
{
	t_fractal	*fractal;

	fractal = (t_fractal *) malloc(sizeof(t_fractal));
	if (!fractal)
		return (NULL);
	fractal->zoom = 1;
	fractal->offset_x = -1.8;
	fractal->offset_y = -0.6;
	fractal->c_re = 0.2;
	fractal->c_im = 0;
	fractal->render = ft_fractal_william;
	fractal->color_func = get_palette_secondary;
	fractal->max_iteration = 30;
	return (fractal);
}

void	ft_fractal_william(void *param)
{
	t_fractal	*fractal;
	t_intvec2	vec;
	t_point		p;
	t_point		complex;
	uint32_t	color;

	fractal = (t_fractal *)param;
	p = get_zoomfactor(fractal->zoom,
			fractal->image->width, fractal->image->height);
	vec.x = 0;
	while (vec.x++ < fractal->image->width)
	{
		vec.y = 0;
		while (++vec.y < fractal->image->height)
		{
			complex.x = 1.5 * vec.x / p.x + fractal->offset_x;
			complex.y = vec.y / -p.y + fractal->offset_y;
			color = get_color(william(complex, fractal->c_re,
						fractal->c_im, fractal->max_iteration),
					fractal->max_iteration, fractal->color_func);
			mlx_put_pixel(fractal->image, vec.x, vec.y, color);
		}
	}
}
