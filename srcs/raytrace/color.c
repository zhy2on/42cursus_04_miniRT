/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:39:36 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/07 02:45:12 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

	rgb[0] = (((double)(c1 >> 0x10) / 0xFF)
			* ((double)(c2 >> 0x10) / 0xFF)) * 0xFF;
	rgb[1] = (((double)((c1 >> 0x08) & 0xFF) / 0xFF)
			* ((double)((c2 >> 0x08) & 0xFF) / 0xFF)) * 0xFF;
	rgb[2] = (((double)(c1 & 0xFF) / 0xFF)
			* ((double)(c2 & 0xFF) / 0xFF)) * 0xFF;
	return ((rgb[0] << 0x10) | (rgb[1] << 0x08) | rgb[2]);
}

int	cadd(int c1, int c2)
{
	int		r;
	int		g;
	int		b;

	r = check_rgb((c1 >> 0x10) + (c2 >> 0x10));
	g = check_rgb((c1 >> 0x08 & 0xFF) + (c2 >> 0x08 & 0xFF));
	b = check_rgb((c1 & 0xFF) + (c2 & 0xFF));
	return ((r << 0x10) | (g << 0x08) | b);
}

t_vec3		reflect_ray(t_p3 ray, t_p3 normal)
{
	return (vsub(vscale(normal, 2 * dot(normal, ray)), ray));
}

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

double	diffuse(t_light light, t_ray ray)
{
	t_vec3		to_light;
	double		cos_with_light;

	to_light = vsub(light.o, ray.hit.point);
	cos_with_light = clamp(dot(normalize(to_light), ray.hit.nv), 0, 1);
	if (cos_with_light <= 0)
		return (0);
	else
		return (light.br * cos_with_light * ALBEDO);
}

int	ccomp(t_light light, t_ray ray)
{
	double	light_bright;

	light_bright = diffuse(light, ray);
	return (cprod(cscale(ray.hit.elem.clr, light_bright), light.clr));
}
