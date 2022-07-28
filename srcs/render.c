/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:36:33 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/28 16:58:55 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	create_ray(t_cam *cam, double x, double y)
{
	t_ray	ray;

	ray.orig = cam->o;
	ray.dir = vadd(vscale(cam->hor, x), vscale(cam->ver, y));
	ray.dir = vadd(ray.dir, cam->llc);
	ray.dir = normalize(vsub(ray.dir, ray.orig));
	return (ray);
}

int	raytrace(t_minirt *rt, t_ray *ray)
{
	ray->hit.time = INFINITY;
	if (rt->scene.figures->flag == PL)
	{
		if (hit_pl(ray, rt->scene.figures))
			return (ray->hit.color);
		else
			return (0);
	}
	return (0);
}

void	mlx_put_pixel2img(t_img *img, int x, int y, int colour)
{
	char	*dst;

	dst = img->addr + (y * img->size + x * (img->bpp / 8));
	*(unsigned int *)dst = colour;
}

void	render_scene(t_minirt *rt, t_cam *cam)
{
	int		x;
	int		y;
	t_ray	ray;
	int		color;

	if (!cam)
		return ;
	cam->img.ptr = mlx_new_image(rt->mlx, rt->win_w, rt->win_h);
	cam->img.addr = mlx_get_data_addr(cam->img.ptr, &cam->img.bpp,
			&cam->img.size, &cam->img.endian);
	if (!cam->img.ptr || !cam->img.addr)
		put_error("fail to set mlx\n");
	y = -1;
	while (++y < (rt->win_h - 1))
	{
		x = -1;
		while (++x < (rt->win_w - 1))
		{
			ray = create_ray(cam, (double)x / rt->win_w, (double)y / rt->win_h);
			color = raytrace(rt, &ray);
			mlx_put_pixel2img(&cam->img, x, (rt->win_h - 1) - y, color);
		}
	}
	if (!rt->save)
		mlx_put_image_to_window(rt->mlx, rt->win, cam->img.ptr, 0, 0);
}
