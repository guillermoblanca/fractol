/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:45:11 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/27 12:55:47 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"
#include "../inc/mlx42/include/MLX42/MLX42.h"

static t_fractal	*ft_choose_algorithm(const char *str)
{
	t_fractal	*fractal;

	fractal = NULL;
	if (ft_strncmp(str, "julia", 6) == 0)
		fractal = create_julia();
	else if (ft_strncmp(str, "william", 8) == 0)
		fractal = create_william();
	else if (ft_strncmp(str, "mandelbrot", 11) == 0)
		fractal = create_mandelbrot();
	if (fractal == NULL)
	{
		exit(EXIT_FAILURE);
	}
	return (fractal);
}

static void	initialize(t_fractal *fractal)
{
	fractal->width = WIDTH;
	fractal->height = HEIGHT;
	fractal->mlx = mlx_init(WIDTH, HEIGHT, "Fract-ol", 1);
	if (fractal->mlx == NULL)
	{
		write(1, "[ERROR]: Cannot initialize MLX Window\n", 39);
		free(fractal);
		exit(EXIT_FAILURE);
	}
	fractal->image = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (fractal->image == NULL)
	{
		mlx_close_window(fractal->mlx);
		free(fractal);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(fractal->mlx, fractal->image, 0, 0) == -1)
	{
		mlx_close_window(fractal->mlx);
		free(fractal);
		exit(EXIT_FAILURE);
	}
}

int32_t	main(int32_t argc, char **argv)
{
	t_fractal	*fractal;

	fractal = NULL;
	if (argc > 1)
		fractal = ft_choose_algorithm(argv[1]);
	else
		ft_fractal_error();
	print_instructions();
	initialize(fractal);
	ft_bindevents(fractal);
	mlx_loop(fractal->mlx);
	ft_close(fractal);
	return (EXIT_SUCCESS);
}
