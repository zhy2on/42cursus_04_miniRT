/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:36:33 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/07 04:04:25 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	create_ray(t_cam *cam, double x, double y)
{
	t_ray	ray;

	ray.o = cam->o;
	ray.dir = vadd(vscale(cam->hor, x), vscale(cam->ver, y));
	ray.dir = vadd(ray.dir, cam->llc);
	ray.dir = normalize(vsub(ray.dir, ray.o));
	return (ray);
}

void	set_pixel_color(t_img *img, int x, int y, int colour)
{
	char	*dst;

	dst = img->addr + (y * img->size + x * (img->bpp / 8));
	*(unsigned int *)dst = colour;
}

void	render_scene(t_minirt *rt, t_cam *cam)
{
	double	x;
	double	y;
	t_ray	ray;
	int		color;

	if (!cam)
		return ;
	cam->img.ptr = mlx_new_image(rt->mlx, rt->scene.xres, rt->scene.yres);
	cam->img.addr = mlx_get_data_addr(cam->img.ptr, &cam->img.bpp,
			&cam->img.size, &cam->img.endian);
	if (!cam->img.ptr || !cam->img.addr)
		put_error("fail to set mlx\n");
	y = -1;
	while (++y < (rt->scene.yres - 1))
	{
		x = -1;
		while (++x < (rt->scene.xres - 1))
		{
			ray = create_ray(cam, x / rt->scene.xres, y / rt->scene.yres);
			color = raytrace(rt, &ray);
			set_pixel_color(&cam->img, x, (rt->scene.yres - 1) - y, color);
		}
	}
	mlx_put_image_to_window(rt->mlx, rt->win, cam->img.ptr, 0, 0);
}
