/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 02:13:12 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/15 02:20:50 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}			t_ray;

t_vec3	ray_at(t_ray r, double t)
{
	return (vadd(r.orig, vmul_n(r.dir, t)));
}

#endif