/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:45:27 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/27 09:44:54 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"

static void	input_colors(t_fractal *fractal)
{
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_1))
		fractal->color_func = get_palette_pimary;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_2))
		fractal->color_func = get_palette_secondary;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_3))
		fractal->color_func = get_palette_third;
}

static void	input_offset(t_fractal *fractal)
{
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(fractal->mlx, MLX_KEY_W))
		fractal->offset_y -= 0.1 / fractal->zoom;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(fractal->mlx, MLX_KEY_S))
		fractal->offset_y += 0.1 / fractal->zoom;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(fractal->mlx, MLX_KEY_A))
		fractal->offset_x -= 0.1 / fractal->zoom;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(fractal->mlx, MLX_KEY_D))
		fractal->offset_x += 0.1 / fractal->zoom;
}

static void	ft_modifyfractal(t_fractal *fractal)
{
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_C))
		fractal->c_re += 0.1 / fractal->zoom;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_V))
		fractal->c_re -= 0.1 / fractal->zoom;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_B))
		fractal->c_im += 0.1 / fractal->zoom;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_N))
		fractal->c_im -= 0.1 / fractal->zoom;
}

void	ft_hook(void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (fractal == NULL)
		return ;
	input_colors(fractal);
	input_offset(fractal);
	ft_modifyfractal(fractal);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_ESCAPE))
		ft_close(fractal);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_T)
		&& fractal->max_iteration > 1)
		fractal->max_iteration--;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_Y)
		&& fractal->max_iteration < 200)
		fractal->max_iteration++;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_Z))
		fractal->zoom += 0.1;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_X))
		fractal->zoom += 0.1;
}

void	ft_scroll(double xdelta, double ydelta, void *param)
{
	int			mouse_x;
	int			mouse_y;
	t_point		nextpoint;
	t_fractal	*fractal;

	fractal = param;
	if (!fractal)
		return ;
	if (ydelta > 0 || xdelta > 0)
		fractal->zoom += 0.1;
	else
		fractal->zoom -= 0.1;
	if (fractal->zoom <= 0.1f)
		fractal->zoom = 0.1f;
	mlx_get_mouse_pos(fractal->mlx, &mouse_x, &mouse_y);
	nextpoint.x = (mouse_x - fractal->width * 0.5)
		/ (fractal->zoom * fractal->width * 0.5);
	nextpoint.y = (mouse_y - fractal->height * 0.5)
		/ (fractal->zoom * fractal->height * 0.5);
	fractal->offset_x = nextpoint.x;
	fractal->offset_y = nextpoint.y;
}
