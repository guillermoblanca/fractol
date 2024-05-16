
#ifndef FRACTALS_H
#define FRACTALS_H
#include <stdint.h>
#include <stdlib.h>
#include "/home/guille/cursus/level2/fract-ol/inc/mlx42/include/MLX42/MLX42.h"

#define MAX_ITER 256

typedef struct s_fractal
{
	mlx_image_t* image;
	mlx_t* mlx;
	double zoom; // Factor de zoom
	double moveX; // Desplazamiento en el eje X
	double moveY; // Desplazamiento en el eje Y
	double cRe; // Parte real del parámetro c
	double cIm; // Parte imaginaria del parámetro c
} t_fractal;

t_fractal *create_julia(mlx_t* mlx, mlx_image_t* image);

t_fractal *create_mandelbrot(mlx_t* mlx, mlx_image_t* image);

void ft_fractal_julia(void* param);

void ft_fractal_mandelbrot(void* param);

uint32_t get_color(int iter, int max_iter);

#endif