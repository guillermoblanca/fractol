/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:45:11 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/23 14:51:56 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "/home/guille/cursus/level2/fract-ol/inc/mlx42/include/MLX42/MLX42.h"
#include "fractals.h"

static t_fractal	*ft_choose_algorithm(const char *str)
{
	t_fractal	*fractal;

	fractal = NULL;
	if (strcmp(str, "julia") == 0)
		fractal = create_julia();
	else if (strcmp(str, "william") == 0)
		fractal = create_william();
	else if (strcmp(str, "mandelbrot") == 0)
		fractal = create_mandelbrot();
	return (fractal);
}

int32_t	main(int32_t argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_fractal	*fractal;

	if (argc > 1)
		fractal = ft_choose_algorithm(argv[1]);
	if (fractal == NULL)
		ft_fractal_error();
	print_instructions();
	if (!(mlx = mlx_init(WIDTH,HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	fractal->width = WIDTH;
	fractal->height = HEIGHT;
	fractal->image = image;
	fractal->mlx = mlx;
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		free(fractal);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	ft_bindevents(fractal);
	mlx_loop(mlx);
	ft_close(fractal);
	return (EXIT_SUCCESS);
}
