/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:24:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/04 17:21:53 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	create_vec3(double x, double y, double z)
{
	t_vec3	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec3	vadd(t_vec3 u, t_vec3 v)
{
	return (create_vec3(u.x + v.x, u.y + v.y, u.z + v.z));
}

t_vec3	vsub(t_vec3 u, t_vec3 v)
{
	return (create_vec3(u.x - v.x, u.y - v.y, u.z - v.z));
}

t_vec3	vscale(t_vec3 u, double n)
{
	return (create_vec3(u.x * n, u.y * n, u.z * n));
}

double	vsin(t_p3 a, t_p3 b)
{
	return (sqrt(1 - pow(vcos(a, b), 2)));
}

double	vcos(t_p3 a, t_p3 b)
{
	return (dot(a, b) / (mod(a) * mod(b)));
}
