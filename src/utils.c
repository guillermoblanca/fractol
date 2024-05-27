/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:52:13 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/27 10:57:23 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	lerp(int min, int max, float delta)
{
	int	inter;

	if (delta < 0)
		delta = 0;
	if (delta > 1)
		delta = 1;
	inter = min + (int)((max - min) * delta);
	return (inter);
}

static int	get_coincidence(char source, const char *dest)
{
	int	i;

	i = 0;
	while (dest[i] != '\0')
	{
		if (dest[i] == source)
			return (i);
		i++;
	}
	return (-1);
}

t_color	hex_to_color(const char *hex)
{
	t_color	c;

	c.r = get_coincidence(hex[0], HEX) * 16 + get_coincidence(hex[1], HEX);
	c.g = get_coincidence(hex[2], HEX) * 16 + get_coincidence(hex[3], HEX);
	c.b = get_coincidence(hex[4], HEX) * 16 + get_coincidence(hex[5], HEX);
	return (c);
}

t_point	get_zoomfactor(double zoom, double imageW, double imageH)
{
	t_point	p;

	p.x = (0.5 * zoom * imageW);
	p.y = (0.5 * zoom * imageH);
	return (p);
}
