/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 02:35:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 00:38:45 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "struct.h"
# include "figures.h"
# include "vec3.h"

# define ALBEDO	0.9

/*
** raytrace.c **
*/
int			intersect(t_minirt *rt, t_ray *ray);
int			in_shadow(t_minirt *rt, t_hit hit, t_light *light);
int			raytrace(t_minirt *rt, t_ray *ray);

/*
** hit_pl_sp.c **
*/
t_p3		get_hit_point(t_ray ray);
void		solve_quadratic(double a, double b, double c, double root[2]);
double		hit_plane_time(t_ray ray, t_plane pl);
int			hit_plane(t_ray *ray, t_figures elem);
int			hit_sphere(t_ray *ray, t_figures elem);

/*
** hit_cy.c **
*/
double		hit_cylinder_time(t_ray ray, t_cylinder cy, double *y);
int			hit_cylinder(t_ray *ray, t_figures elem);

/*
** color.c **
*/
int			cscale(int color, double d);
int			cprod(int c1, int c2);
int			cadd(int c1, int c2);
int			ccomp(t_light light, t_ray ray);

/*
** lighting.c **
*/
double		diffuse(t_light light, t_ray ray);
int			lighting(t_light light, t_ray ray);

#endif