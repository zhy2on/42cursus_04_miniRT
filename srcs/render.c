/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:36:33 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/28 20:44:59 by jihoh            ###   ########.fr       */
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

int	check_rgb(int n)
{
	if (n > 0xFF)
		return (0xFF);
	else if (n < 0)
		return (0);
	else
		return (n);
}

int	cscale(int color, double d)
{
	int		rgb[3];

	rgb[0] = check_rgb(d * (color >> 0x10));
	rgb[1] = check_rgb(d * ((color >> 0x08) & 0xFF));
	rgb[2] = check_rgb(d * (color & 0xFF));
	return ((rgb[0] << 0x10) | (rgb[1] << 0x08) | rgb[2]);
}

int	cprod(int c1, int c2)
{
	int	rgb[3];

	rgb[0] = (((float)(c1 >> 0x10) / 0xFF)
			* ((float)(c2 >> 0x10) / 0xFF)) * 0xFF;
	rgb[1] = (((float)((c1 >> 0x08) & 0xFF) / 0xFF)
			* ((float)((c2 >> 0x08) & 0xFF) / 0xFF)) * 0xFF;
	rgb[2] = (((float)(c1 & 0xFF) / 0xFF)
			* ((float)(c2 & 0xFF) / 0xFF)) * 0xFF;
	return ((rgb[0] << 0x10) | (rgb[1] << 0x08) | rgb[2]);
}

void	get_sphere_root(double root[2], t_ray *ray, t_sphere sp)
{
	double	discriminant;
	t_p3	oc;
	double	k[3];

	oc = vsub(ray->o, sp.c);
	k[0] = dot(ray->dir, ray->dir);
	k[1] = 2 * dot(ray->dir, oc);
	k[2] = dot(oc, oc) - sp.r * sp.r;
	discriminant = k[1] * k[1] - (4 * k[0] * k[2]);
	if (discriminant < 0)
	{
		root[0] = INFINITY;
		root[1] = INFINITY;
	}
	else
	{
		root[0] = (-k[1] + sqrt(discriminant)) / (2 * k[0]);
		root[1] = (-k[1] - sqrt(discriminant)) / (2 * k[0]);
	}
}

t_p3	get_hit_point(t_ray ray)
{
	return (vadd(ray.o, vscale(ray.dir, ray.hit.time)));
}

int	hit_sphere(t_figures *elem, t_ray *ray)
{
	double		time[2];
	t_sphere	sp;

	sp = elem->fig.sp;
	get_sphere_root(time, ray, sp);
	if (ray->hit.time > time[0] && time[0] > 0)
	{
		ray->hit.time = time[0];
		ray->hit.point = get_hit_point(*ray);
		ray->hit.nv = normalize(vsub(ray->hit.point, sp.c));
		ray->hit.color = elem->color;
		return (1);
	}
	// printf("hi\n");
	return (0);
}

int	intersect(t_minirt *rt, t_ray *ray)
{
	int			ret;
	t_figures	*elem;

	ray->hit.time = INFINITY;
	ret = 0;
	elem = rt->scene.figures;
	while (elem)
	{
		if (elem->flag == SP)
			ret = hit_sphere(elem, ray);
		elem = elem->next;
	}
	return (ret);
}

int	raytrace(t_minirt *rt, t_ray *ray)
{
	int		al_color;
	int		color;

	if (!intersect(rt, ray))
		return (0);
	al_color = cscale(rt->scene.al_color, rt->scene.al_ratio);
	color = cprod(ray->hit.color, al_color);
	return (color);
}

void		mlx_put_pixel2img(t_img *img, int x, int y, int colour)
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
