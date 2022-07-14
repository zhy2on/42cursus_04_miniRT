/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 03:02:52 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/15 03:29:18 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

# include "vec3.h"
# include "ray.h"

typedef struct s_hit_record {
	t_vec3	p;
	t_vec3	normal;
	double	t;
	int		front_face;
}			t_hit_record;

void	set_face_normal(t_hit_record *hit_record, t_ray r,
			t_vec3 outward_normal)
{
	hit_record->front_face = dot(r.dir, outward_normal) < 0;
	if (hit_record->front_face)
		hit_record->normal = outward_normal;
	else
		hit_record->normal = -outward_normal;
}

#endif