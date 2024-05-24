/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:52:13 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/23 14:52:15 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"

static int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int lerp(int min, int max, float delta)
{
    if (delta < 0)
        delta  = 0;
    if (delta > 1)
        delta = 1;

    int inter = min + (int)((max - min) * delta);
    return inter;
}

t_color get_palette_pimary(int iteration)
{
	static t_color c[5];
    static int initialized;

    if (!initialized)
    {
        c[0] = (t_color){1, 25,35};
	    c[1] = (t_color){1, 35,32};
	    c[2] = (t_color){1, 45,37};
	    c[3] = (t_color){1, 55,24};
	    c[4] = (t_color){70, 75,3};
        initialized = 1;
    }
    if (iteration < 0 || iteration >= 5)
        return (t_color){0,0,0};

    return c[iteration];
}
t_color get_palette_secondary(int iteration)
{
    static t_color c[5];
    static int initialized;

    if (!initialized)
    {
        c[0] = (t_color){106, 247, 153};
        c[1] = (t_color){255, 205, 117};
        c[2] = (t_color){249, 103, 80};
        c[3] = (t_color){143, 124, 162};
        c[4] = (t_color){104, 120, 47};
        initialized = 1;
    }
    if (iteration < 0 || iteration >= 5)
        return ((t_color){255,0,0});
    return (c[iteration]);
}

t_color lerp_color(t_color a, t_color b, float delta)
{
    t_color c;

    c.r = lerp(a.r, b.r, delta);
    c.g = lerp(a.g, b.g, delta);
    c.b = lerp(a.b, b.b, delta);
    return (c);
}

t_color get_palette_third(int iteration)
{
    static t_color c[5];
    static int initialized;

    if (!initialized)
    {
        c[0] = hex_to_color("FA4BD0");
	    c[1] = hex_to_color("4BFAF7");
	    c[2] = hex_to_color("FADE4B");
	    c[3] = hex_to_color("A59B68");
	    c[4] = hex_to_color("7A6275");
        initialized = 1;
    }
    if (iteration < 0 || iteration >= 5)
        return ((t_color){255,0,0});
    return (c[iteration]);
}

// Función para determinar el color en función del número de iteraciones
uint32_t get_color(int iter, int max_iter, t_color_func func) 
{
    t_color c;
    float delta;

    delta = (float)iter /(float) max_iter;
    c = func(lerp(0,4,delta));
    return ft_pixel(c.r, c.g, c.b, lerp(0,255, delta));
}

// Función para determinar el color en función del número de iteraciones
uint32_t get_color_interpolated(int iter, int max_iter, float interpolation) 
{
    t_color a;
    t_color b;
    t_color c;
    float delta;

    delta = (float)iter /(float) max_iter;
    a = get_palette_pimary(lerp(0,4,delta));
    b = get_palette_secondary(lerp(0,4,delta));
    c = lerp_color(a, b, interpolation);
    return ft_pixel(c.r, c.g, c.b, 0xFF);
}

t_point get_zoomfactor(double zoom, double imageW, double imageH)
{
    t_point p;

    p.x = (0.5 * zoom * imageW);
    p.y = (0.5 * zoom * imageH);
    return (p);
}

static int get_coincidence(char source, const char *dest)
{
    int i;

    i = 0;
    while (dest[i] != '\0') {
        if (dest[i] == source) {
            return i;
        }
        i++;
    }
    return -1;
}

t_color hex_to_color(const char *hex)
{
    t_color c;

    c.r = get_coincidence(hex[0],HEX) * 16 + get_coincidence(hex[1],HEX);
    c.g = get_coincidence(hex[2],HEX) * 16 + get_coincidence(hex[3],HEX);
    c.b = get_coincidence(hex[4],HEX) * 16 + get_coincidence(hex[5],HEX);
    return c;
}