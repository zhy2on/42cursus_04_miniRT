/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:39:36 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/06 22:12:32 by jihoh            ###   ########.fr       */
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

	rgb[0] = (((float)(c1 >> 0x10) / 0xFF)
			* ((float)(c2 >> 0x10) / 0xFF)) * 0xFF;
	rgb[1] = (((float)((c1 >> 0x08) & 0xFF) / 0xFF)
			* ((float)((c2 >> 0x08) & 0xFF) / 0xFF)) * 0xFF;
	rgb[2] = (((float)(c1 & 0xFF) / 0xFF)
			* ((float)(c2 & 0xFF) / 0xFF)) * 0xFF;
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

// int	ccomp(t_light *light, t_ray ray, t_minirt *rt)
// {
// 	t_vec3		light_normal;
// 	float		gain;
// 	float		r2;
// 	float		light_bright;
// 	t_vec3		relfected;
// 	t_vec3		p_to_cam;
	
// 	(void)rt;
// 	light_normal = vsub(light->o, ray.hit.point);
// 	r2 = length_squared(light_normal);
// 	p_to_cam = vsub(ray.o, ray.hit.point);
// 	relfected = reflect_ray(light_normal, ray.hit.nv);
// 	gain = dot(normalize(light_normal), ray.hit.nv);
// 	// gain = dot(relfected, ray.hit.nv);
// 	// gain = dot(normalize(relfected), p_to_cam);
// 	if (gain <= 0)
// 		light_bright = 0;
// 	else
// 	{
// 		light_bright = light->br * pow(gain, rt->scene.figures->specular);
// 		light_bright += (light->br * gain * ALBEDO) / (4.0 * M_PI * r2);
// 	}
// 	// cadd(light_bright, light->clr);
// 	return (cprod(cadd(0, cscale(ray.hit.clr, light_bright)), light->clr));
// }

////
int	ccomp(t_light *light, t_ray ray, t_minirt *rt)
{
	t_vec3		light_normal;
	float		gain;
	float		r2;
	float		light_bright;
	t_vec3		relfected;
	t_vec3		p_to_cam;
	
	(void)rt;
	light_normal = vsub(light->o, ray.hit.point);
	r2 = length_squared(light_normal);
	p_to_cam = vsub(ray.o, ray.hit.point);
	relfected = reflect_ray(light_normal, ray.hit.nv);
	gain = dot((light_normal), ray.hit.nv);
	// gain = dot(relfected, ray.hit.nv);
	// gain = dot(normalize(relfected), p_to_cam);
	// if (gain > 0)
	if (dot(relfected, p_to_cam) > 0)
	{
		light_bright = light->br * pow(vcos(relfected, p_to_cam), rt->scene.figures->specular);
	}
	else
	{
		light_bright = 0;
	}
	// cadd(light_bright, light->clr);
	light_bright += (light->br * gain * ALBEDO) / (4.0 * M_PI * r2);
	return (cprod(cadd(0, cscale(ray.hit.elem.clr, light_bright)), light->clr));
}
