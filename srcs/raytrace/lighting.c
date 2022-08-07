/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 02:58:21 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/07 14:57:31 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
* diffuse = (albedo) * (light_intensity) * (cosine to_light and hit nv)
* diffuse can get different result thorugh cosine p_to_light and hit_nv
* dot = |a| * |b| * cos(a, b)
* if a and b are both normal vectors,
  the result of the dot product is equal to the cosine value
*/
double	diffuse(t_light light, t_ray ray)
{
	t_vec3		p_to_light;
	double		cos_with_light;

	p_to_light = vsub(light.o, ray.hit.point);
	cos_with_light = clamp(dot(normalize(p_to_light), ray.hit.nv), 0, 1);
	if (cos_with_light > 0)
		return (ALBEDO * light.br * cos_with_light);
	else
		return (0);
}

/*
* R = 2(L·N)N - L
* L : p_to_light vector
* N : normal vector at hit point
* R : reflected vector
*/
t_vec3	reflect_ray(t_vec3 p_to_light, t_vec3 hit_normal)
{
	return (vsub(vscale(hit_normal, 2 * dot(p_to_light, hit_normal)), \
					p_to_light));
}

/*
* can get different shade through (V⋅R)^n graph
* n is user variable
*/
double	specular(t_light light, t_ray ray)
{
	t_vec3	p_to_light;
	t_vec3	reflected;
	t_vec3	p_to_cam;
	double	scalar;

	p_to_light = vsub(light.o, ray.hit.point);
	reflected = reflect_ray(normalize(p_to_light), ray.hit.nv);
	p_to_cam = vscale(ray.dir, -1);
	scalar = dot(normalize(reflected), normalize(p_to_cam));
	if (ray.hit.elem.specular > 0 && scalar > 0)
		return (light.br * pow(scalar, ray.hit.elem.specular));
	else
		return (0);
}

int	lighting(t_light light, t_ray ray)
{
	double	light_bright;

	light_bright = diffuse(light, ray) + specular(light, ray);
	return (cprod(cscale(ray.hit.elem.clr, light_bright), light.clr));
}
