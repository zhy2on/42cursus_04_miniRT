/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:24:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/17 19:20:42 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>

typedef struct s_vec3
{
	double	e[3];
}				t_vec3;

typedef t_vec3	t_p3;
typedef t_vec3	t_clr;

t_vec3	get_vec3(double e0, double e1, double e2)
{
	t_vec3	ret;

	ret.e[0] = e0;
	ret.e[1] = e1;
	ret.e[2] = e2;
	return (ret);
}

t_vec3	vadd(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.e[0] = u.e[0] + v.e[0];
	ret.e[1] = u.e[1] + v.e[1];
	ret.e[2] = u.e[2] + v.e[2];
	return (ret);
}

t_vec3	vsub(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.e[0] = u.e[0] - v.e[0];
	ret.e[1] = u.e[1] - v.e[1];
	ret.e[2] = u.e[2] - v.e[2];
	return (ret);
}

t_vec3	vmul(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.e[0] = u.e[0] * v.e[0];
	ret.e[1] = u.e[1] * v.e[1];
	ret.e[2] = u.e[2] * v.e[2];
	return (ret);
}

t_vec3	vmul_n(t_vec3 u, double n)
{
	t_vec3	ret;

	ret.e[0] = u.e[0] * n;
	ret.e[1] = u.e[1] * n;
	ret.e[2] = u.e[2] * n;
	return (ret);
}

t_vec3	vdiv(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.e[0] = u.e[0] / v.e[0];
	ret.e[1] = u.e[1] / v.e[1];
	ret.e[2] = u.e[2] / v.e[2];
	return (ret);
}

t_vec3	vdiv_n(t_vec3 u, double n)
{
	t_vec3	ret;

	ret.e[0] = u.e[0] / n;
	ret.e[1] = u.e[1] / n;
	ret.e[2] = u.e[2] / n;
	return (ret);
}

double	dot(t_vec3 u, t_vec3 v)
{
	return (u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]);
}

t_vec3	cross(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.e[0] = u.e[1] * v.e[2] - u.e[2] * v.e[1];
	ret.e[1] = u.e[2] * v.e[0] - u.e[0] * v.e[2];
	ret.e[2] = u.e[0] * v.e[1] - u.e[1] * v.e[0];
	return (ret);
}

double	length_squared(t_vec3 v)
{
	return (v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
}

double	length(t_vec3 v)
{
	return (sqrt(length_squared(v)));
}

#endif