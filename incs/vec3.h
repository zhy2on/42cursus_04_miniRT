/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:24:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/26 17:45:34 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef t_vec3	t_p3;
typedef t_vec3	t_clr;

t_vec3	create_vec3(double x, double y, double z);

t_vec3	vadd(t_vec3 u, t_vec3 v);

t_vec3	vsub(t_vec3 u, t_vec3 v);

t_vec3	vmul(t_vec3 u, t_vec3 v);

t_vec3	vscale(t_vec3 u, double n);

t_vec3	vdiv(t_vec3 u, t_vec3 v);

t_vec3	vdiv_n(t_vec3 u, double n);

double	dot(t_vec3 u, t_vec3 v);

t_vec3	cross(t_vec3 u, t_vec3 v);

double	length_squared(t_vec3 v);

double	length(t_vec3 v);

t_vec3	normalize(t_vec3 v);

#endif