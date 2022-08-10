/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 02:58:21 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/10 18:01:46 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	lighting(t_light light, t_ray ray)
{
	double	light_bright;

	light_bright = diffuse(light, ray);
	return (cprod(cscale(ray.hit.elem.clr, light_bright), light.clr));
}
