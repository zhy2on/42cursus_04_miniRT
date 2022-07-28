/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:24:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/26 19:12:09 by junyopar         ###   ########.fr       */
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

t_vec3	vmul(t_vec3 u, t_vec3 v)
{
	return (create_vec3(u.x * v.x, u.y * v.y, u.z * v.z));
}

t_vec3	vscale(t_vec3 u, double n)
{
	return (create_vec3(u.x * n, u.y * n, u.z * n));
}

t_vec3	vdiv(t_vec3 u, t_vec3 v)
{
	return (create_vec3(u.x / v.x, u.y / v.y, u.z / v.z));
}

t_vec3	vdiv_n(t_vec3 u, double n)
{
	return (create_vec3(u.x / n, u.y / n, u.z / n));
}

double	dot(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	cross(t_vec3 u, t_vec3 v)
{
	return (create_vec3(u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x));
}

double	length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	length(t_vec3 v)
{
	return (sqrt(length_squared(v)));
}

t_vec3	normalize(t_vec3 v)
{
	double	mod;

	mod = length(v);
	return (create_vec3(v.x / mod, v.y / mod, v.z / mod));
}
