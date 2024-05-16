// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "/home/guille/cursus/level2/fract-ol/inc/mlx42/include/MLX42/MLX42.h"
#include "fractals.h"

#define WIDTH 512
#define HEIGHT 512
// -----------------------------------------------------------------------------

void ft_hook(void* param)
{
	t_fractal* fractal = param;

	if (mlx_is_key_down(fractal->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fractal->mlx);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_UP))
		fractal->moveY -= 0.1;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_DOWN))
		fractal->moveY += 0.1;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_LEFT))
		fractal->moveX -= 0.1;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_RIGHT))
		fractal->moveX += 0.1;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_E))
		fractal->zoom += 0.1;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_D))
		fractal->zoom -= 0.1;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_C))
		fractal->cRe += 0.1;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_V))
		fractal->cRe -= 0.1;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_B))
		fractal->cIm += 0.1;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_N))
		fractal->cIm -= 0.1;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_R))
	{
		printf("Zoom %f MoveX %f MoveY %f\n", fractal->zoom, fractal->moveX, fractal->moveY);
		printf("cRe %f cIm %f\n", fractal->cRe, fractal->cIm);
	}
}
void ft_scroll(double xdelta, double ydelta, void* param)
{
	int mouseX;
	int mouseY;
	t_fractal* fractal;

	fractal = param;
	if (!fractal)
		return;
	if (ydelta > 0 || xdelta > 0)
		fractal->zoom += 0.1;
	else
		fractal->zoom -= 0.1;
	mlx_get_mouse_pos(fractal->mlx, &mouseX, &mouseY);
	fractal->moveX = (mouseX - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH);
	fractal->moveY = (mouseY - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT);
}

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, char** argv)
{
	mlx_t* mlx;
	mlx_image_t* image;
	t_fractal *fractal;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
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
	fractal = create_julia(mlx, image);
	if (argc == 3)
	{
		fractal->cRe = atoi(argv[1]);
		fractal->cIm = atoi(argv[2]);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_fractal_mandelbrot, fractal);
	mlx_loop_hook(mlx, ft_hook, fractal);
	mlx_scroll_hook(mlx, ft_scroll, fractal);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free(fractal);
	return (EXIT_SUCCESS);
}
