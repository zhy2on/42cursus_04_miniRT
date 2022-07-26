/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:24:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/26 14:58:31 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	get_vec3(double e0, double e1, double e2)
{
	t_vec3	ret;

	ret.x = e0;
	ret.y = e1;
	ret.z = e2;
	return (ret);
}

t_vec3	vadd(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.x = u.x + v.x;
	ret.y = u.y + v.y;
	ret.z = u.z + v.z;
	return (ret);
}

t_vec3	vsub(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.x = u.x - v.x;
	ret.y = u.y - v.y;
	ret.z = u.z - v.z;
	return (ret);
}

t_vec3	vmul(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.x = u.x * v.x;
	ret.y = u.y * v.y;
	ret.z = u.z * v.z;
	return (ret);
}

t_vec3	vmul_n(t_vec3 u, double n)
{
	t_vec3	ret;

	ret.x = u.x * n;
	ret.y = u.y * n;
	ret.z = u.z * n;
	return (ret);
}

t_vec3	vdiv(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.x = u.x / v.x;
	ret.y = u.y / v.y;
	ret.z = u.z / v.z;
	return (ret);
}

t_vec3	vdiv_n(t_vec3 u, double n)
{
	t_vec3	ret;

	ret.x = u.x / n;
	ret.y = u.y / n;
	ret.z = u.z / n;
	return (ret);
}

double	dot(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	cross(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.x = u.y * v.z - u.z * v.y;
	ret.y = u.z * v.x - u.x * v.z;
	ret.z = u.x * v.y - u.y * v.x;
	return (ret);
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
	t_vec3	nv;
	double	mod;

	mod = length(v);
	nv.x = v.x / mod;
	nv.y = v.y / mod;
	nv.z = v.z / mod;
	return (nv);
}
