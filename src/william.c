/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   william.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:44:53 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/23 14:45:00 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"
#include <math.h>

static int william(double pr, double pi, double re, double im, int max_iteration)
{
    int i;
    t_point newp;
    t_point oldp;
    
    i = 0;
    newp.x = re;
    newp.y = im;
    while (i++ < max_iteration)
    {
        oldp.x = newp.x;
        oldp.y = newp.y;
        newp.x = fabs(oldp.x * oldp.x - oldp.y * oldp.y + pr);
        newp.y =2 * oldp.x * oldp.y + pi;
        if ((newp.x * newp.x + newp.y * newp.y) > 4) 
            break;
    }
    return (i);
}

t_fractal *create_william()
{
    t_fractal* fractal;

    fractal = malloc(sizeof(t_fractal));
    if (!fractal) 
        return (NULL);
    fractal->zoom = 1;
    fractal->offset_x = -1.8;
	fractal->offset_y = -0.9;
    fractal->c_re = 0;
    fractal->c_im = 0;
    fractal->render = ft_fractal_william;
    fractal->color_func = get_palette_secondary;
    fractal->max_iteration = 30;
    return (fractal);
}

void ft_fractal_william(void* param) {

    t_fractal* fractal;
    uint32_t x;
    uint32_t y;
    t_point p;

    fractal = (t_fractal*)param;
    p = get_zoomfactor(fractal->zoom, fractal->image->width, fractal->image->height);
    x = 0;
    while (x++ < fractal->image->width)
    {
        y = 0;
        while(++y < fractal->image->height)
        {
            double pi = 1.5 * x / p.x + fractal->offset_x;
            double pr = y / p.y + fractal->offset_y;
            uint32_t color = get_color(
                william(pr, pi, fractal->c_re, fractal->c_im, fractal->max_iteration),
                 fractal->max_iteration,
                 fractal->color_func);
            mlx_put_pixel(fractal->image, x, y, color);
        }
    }
}
