/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   information.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:52:28 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/23 14:58:02 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"

static void	print_colors(void)
{
	printf("---------------------------------------------\n");
	printf("KEY 1: First palette\n");
	printf("KEY 2: Second palette\n");
	printf("KEY 3: Third palette\n");
	printf("---------------------------------------------\n");
}

static void	print_controllers(void)
{
	printf("-------------MOVE CONTROLLERS----------------\n");
	printf("ARROW UP OR    KEY W ----> MOVE UP\n");
	printf("ARROW DOWN OR  KEY S ----> MOVE DOWN\n");
	printf("ARROW RIGHT OR KEY D ----> MOVE RIGTH\n");
	printf("ARROW LEFT OR  KEY A ----> MOVE LEFT\n");
	printf("MOUSE SCROLL         ----> ZOOM\n");
	printf("Z(+)  /   X(-)       ----> ZOOM\n");
}

static void	print_algorithms(void)
{
	printf("Choose the algorithm using argumments\n");
	printf("mandelbrot\n");
	printf("julia\n");
	printf("william\n");
}

void	print_instructions(void)
{
	printf("---------------------------------------------\n");
	printf("-------------------FRACTOL-------------------\n");
	print_algorithms();
	printf("---------------------------------------------\n");
	print_controllers();
	printf("---------------------------------------------\n");
	printf("T: Reduce iterations\n");
	printf("Y Increment iterations\n");
	printf("---------------------------------------------\n");
	print_colors();
}

static void	print_fractal_error(void)
{
	printf("Error you need to choose a valid algorithm before continuing\n");
}

void	ft_fractal_error(void)
{
	print_fractal_error();
	print_algorithms();
	exit(EXIT_FAILURE);
}
