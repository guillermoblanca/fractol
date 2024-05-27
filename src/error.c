/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:42:29 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/27 12:46:13 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"

static void	ft_resizewindow(int32_t width, int32_t height, void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	mlx_resize_image(fractal->image, width, height);
}

static void	print_fractal_error(void)
{
	write(1, "Error you need to choose a valid algorithm before continuing\n",
		62);
}

void	ft_fractal_error(void)
{
	print_fractal_error();
	print_algorithms();
	exit(EXIT_FAILURE);
}

void	ft_bindevents(void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	mlx_resize_hook(fractal->mlx, ft_resizewindow, param);
	mlx_loop_hook(fractal->mlx, fractal->render, fractal);
	mlx_loop_hook(fractal->mlx, ft_hook, fractal);
	mlx_scroll_hook(fractal->mlx, ft_scroll, fractal);
}

void	ft_close(void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *) param;
	mlx_terminate(fractal->mlx);
	if (fractal != NULL)
	{
		free(fractal);
		fractal = NULL;
	}
	exit(EXIT_SUCCESS);
}
