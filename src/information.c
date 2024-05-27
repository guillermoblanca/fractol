/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   information.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:52:28 by gblanca           #+#    #+#             */
/*   Updated: 2024/05/27 11:39:22 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"

static void	print_colors(void)
{
	write(1, "---------------------------------------------\n", 47);
	write(1, "KEY 1: First palette\n", 22);
	write(1, "KEY 2: Second palette\n", 23);
	write(1, "KEY 3: Third palette\n", 22);
	write(1, "---------------------------------------------\n", 47);
}

static void	print_controllers(void)
{
	write(1, "-------------MOVE CONTROLLERS----------------\n", 47);
	write(1, "ARROW UP OR    KEY W ----> MOVE UP\n", 36);
	write(1, "ARROW DOWN OR  KEY S ----> MOVE DOWN\n", 38);
	write(1, "ARROW RIGHT OR KEY D ----> MOVE RIGTH\n", 39);
	write(1, "ARROW LEFT OR  KEY A ----> MOVE LEFT\n", 38);
	write(1, "MOUSE SCROLL         ----> ZOOM\n", 33);
	write(1, "Z(+)  /   X(-)       ----> ZOOM\n", 33);
}

void	print_algorithms(void)
{
	write(1, "Choose the algorithm using argumments\n", 39);
	write(1, "mandelbrot\n", 12);
	write(1, "julia\n", 7);
	write(1, "william\n", 9);
}

void	print_instructions(void)
{
	write(1, "---------------------------------------------\n", 47);
	write(1, "-------------------FRACTOL-------------------\n", 47);
	print_algorithms();
	write(1, "---------------------------------------------\n", 47);
	print_controllers();
	write(1, "---------------------------------------------\n", 47);
	write(1, "T: Reduce iterations\n", 22);
	write(1, "Y Increment iterations\n", 24);
	write(1, "---------------------------------------------\n", 47);
	print_colors();
}
