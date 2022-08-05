/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 02:18:49 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/04 17:21:18 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

double	mod(t_p3 v)
{
	return (sqrt(dot(v, v)));
}

t_vec3	cross(t_vec3 u, t_vec3 v)
{
	return (create_vec3(u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x));
}

t_vec3	normalize(t_vec3 v)
{
	double	mod;

	mod = sqrt(length_squared(v));
	return (create_vec3(v.x / mod, v.y / mod, v.z / mod));
}

double	length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	distance(t_vec3 u, t_vec3 v)
{
	double	d;

	d = sqrt(pow(v.x - u.x, 2) + pow(v.y - u.y, 2) + pow(v.z - u.z, 2));
	return (d);
}
