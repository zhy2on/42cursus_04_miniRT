/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 02:35:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/04 02:45:07 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "struct.h"
# include "figures.h"
# include "vec3.h"

/*
** raytrace.c **
*/
int		intersect(t_minirt *rt, t_ray *ray);
int		in_shadow(t_minirt *rt, t_hit hit, t_light *light);
int		raytrace(t_minirt *rt, t_ray *ray);

/*
** hit.c **
*/
double	hit_plane_time(t_p3 o, t_vec3 dir, t_p3 p, t_vec3 nv);
int		hit_plane(t_ray *ray, t_figures *elem);
int		hit_sphere(t_ray *ray, t_figures *elem);
double	hit_caps_time(t_ray ray, t_cylinder cy);
int		hit_caps(t_ray *ray, t_figures *elem);
double	hit_cylinder_time(t_ray ray, t_cylinder cy, double *y);
int		hit_cylinder(t_ray *ray, t_figures *elem);

#endif