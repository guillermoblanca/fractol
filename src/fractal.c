
#include "fractals.h"

static int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

t_fractal *create_julia(mlx_t* mlx, mlx_image_t* image)
{
    t_fractal* fractal;

    fractal = malloc(sizeof(t_fractal));
    if (!fractal) return (NULL);
    fractal->image = image;
    fractal->mlx = mlx;
    fractal->zoom = 1.3;
    fractal->moveX = -1.3;
    fractal->moveY = -0.8;
    fractal->cRe = -0.7;
    fractal->cIm = 0.27015;
    return (fractal);
}

t_fractal *create_mandelbrot(mlx_t *mlx, mlx_image_t *image)
{
    t_fractal* fractal;

    fractal = malloc(sizeof(t_fractal));
    if (!fractal) return (NULL);
    fractal->image = image;
    fractal->mlx = mlx;
    fractal->zoom = 1;
    fractal->moveX = 0;
    fractal->moveY = 0;
    fractal->cRe = 0;
    fractal->cIm = 0;
    return (fractal);
}

void ft_fractal_julia(void* param) {
    t_fractal* fractal = (t_fractal*)param;
	uint32_t x, y;

    for (x = 0; x < fractal->image->width; x++) {
        for (y = 0; y < fractal->image->height; y++) {
            double newRe = 1.5 * x / (0.5 * fractal->zoom * fractal->image->width) + fractal->moveX;
            double newIm = y / (0.5 * fractal->zoom * fractal->image->height) + fractal->moveY;

            int i;
            for (i = 0; i < MAX_ITER; i++) {
                double oldRe = newRe;
                double oldIm = newIm;

                newRe = oldRe * oldRe - oldIm * oldIm + fractal->cRe;
                newIm = 2 * oldRe * oldIm + fractal->cIm;

                if ((newRe * newRe + newIm * newIm) > 4) break; // Punto fuera del conjunto
            }

            uint32_t color = get_color(i, MAX_ITER);
            mlx_put_pixel(fractal->image, x, y, color);
        }
    }
}

void ft_fractal_mandelbrot(void* param) {
    t_fractal* fractal = (t_fractal*)param; // Suponiendo que tienes una estructura de imagen

    for (uint32_t x = 0; x < fractal->image->width; x++) {
        for (uint32_t y = 0; y < fractal->image->height; y++) {
            // Mapear el punto (x, y) al plano complejo
            double pr = 1.5 * x / (0.5 * fractal->zoom * fractal->image->width) + fractal->moveX;
            double pi = y / (0.5 * fractal->zoom * fractal->image->height) + fractal->moveY;

            // Iterar sobre la fórmula de Mandelbrot
            double newRe = fractal->cRe, newIm = fractal->cIm, oldRe, oldIm;
            int i;
            for (i = 0; i < MAX_ITER; i++) {
                oldRe = newRe;
                oldIm = newIm;

                // z = z^2 + c
                newRe = oldRe * oldRe - oldIm * oldIm + pr;
                newIm = 2 * oldRe * oldIm + pi;

                // Si el punto se escapa al infinito
                if ((newRe * newRe + newIm * newIm) > 4) break;
            }

            uint32_t color = get_color(i, MAX_ITER);
            mlx_put_pixel(fractal->image, x, y, color);
        }
    }
}

// Función para determinar el color en función del número de iteraciones
uint32_t get_color(int iter, int max_iter) {
    if (iter == max_iter) {
        return ft_pixel(0, 0, 0, 0xFF); // Negro para los puntos dentro del conjunto
    }
    // Gradiente de color para los puntos fuera del conjunto
    uint8_t r = (iter * 2) % 256;
    uint8_t g = (iter * 8) % 256;
    uint8_t b = (iter * 6) % 256;
    return ft_pixel(r, g, b, 0xFF);
}

