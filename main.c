/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 00:21:38 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/15 02:57:51 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			WIN_W, WIN_H, "jihoh's fractol");
	mlx->data.img = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	mlx->data.buff = mlx_get_data_addr(mlx->data.img, &mlx->data.bpp,
			&mlx->data.bpl, &mlx->data.endian);
}

t_vec3	ray_color(t_ray r)
{
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

void	draw_scene(void)
{
	t_loop_var	var;
	t_vec3		pixel_color;
	t_cam		cam;
	t_ray		ray;

	cam = init_cam();
	var.j = WIN_H - 1;
	while (var.j >= 0)
	{
		printf("\rScanlines remaining: %d \033[<N>C", var.j);
		var.i = 0;
		while (var.i < WIN_W)
		{
			var.s = 0;
			while (var.s < SAMPLES_PER_PIXEL)
			{
				var.u = (var.i + random_double()) / (WIN_W - 1);
				var.v = (var.j + random_double()) / (WIN_H - 1);
				ray = get_ray(cam, var.u, var.v);
				pixel_color = vadd(pixel_color, ray_color(r, world));
				var.s++;
			}
			var.i++;
		}
		var.j--;
	}
}

int	main(void)
{
	t_mlx			mlx;

	init_mlx(&mlx);
	draw_scene();
	mlx_loop(mlx.mlx_ptr);
}
