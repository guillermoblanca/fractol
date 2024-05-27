/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:51:34 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/27 11:13:58 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"

t_color	get_palette_pimary(int iteration)
{
	static t_color	c[5];
	static int		initialized;

	if (!initialized)
	{
		c[0] = (t_color){1, 25, 35};
		c[1] = (t_color){1, 35, 32};
		c[2] = (t_color){1, 45, 37};
		c[3] = (t_color){1, 55, 24};
		c[4] = (t_color){70, 75, 3};
		initialized = 1;
	}
	if (iteration < 0 || iteration >= 5)
		return ((t_color){0, 0, 0});
	return (c[iteration]);
}

t_color	get_palette_secondary(int iteration)
{
	static t_color	c[5];
	static int		initialized;

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
		return ((t_color){255, 0, 0});
	return (c[iteration]);
}

t_color	lerp_color(t_color a, t_color b, float delta)
{
	t_color	c;

	c.r = lerp(a.r, b.r, delta);
	c.g = lerp(a.g, b.g, delta);
	c.b = lerp(a.b, b.b, delta);
	return (c);
}

t_color	get_palette_third(int iteration)
{
	static t_color	c[5];
	static int		initialized;

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
		return ((t_color){255, 0, 0});
	return (c[iteration]);
}

uint32_t	get_color(int iter, int max_iter, t_color_func func)
{
	t_color	c;
	float	delta;

	delta = (float)iter / (float) max_iter;
	c = func(lerp(0, 4, delta));
	return (ft_pixel(c.r, c.g, c.b, lerp(0, 255, delta)));
}
