/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 06:17:56 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 07:08:06 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	uv_mapping_plane(double *u, double *v, t_hit hit)
{
	t_vec3	vec3_u;
	t_vec3	vec3_v;

	set_uv_axis(hit.nv, &vec3_u, &vec3_v);
	*u = fmod(dot(hit.point, vec3_u), 1);
	if (*u < 0)
		*u += 1;
	*v = fmod(dot(hit.point, vec3_v), 1);
	if (*v < 0)
		*v += 1;
}

void	uv_mapping_sphere(double *u, double *v, t_hit hit)
{
	t_vec3	vec3_u;
	t_vec3	vec3_v;
	double	theta;
	double	phi;

	set_uv_axis(hit.nv, &vec3_u, &vec3_v);
	theta = acos(-1 * hit.nv.y);
	phi = atan2(-1 * hit.nv.z, hit.nv.x) + M_PI;
	*u = phi * M_1_PI * 0.5;
	*v = theta * M_1_PI;
}

void	uv_mapping_cylinder(double *u, double*v, t_hit hit)
{
	t_vec3	vec3_u;
	t_vec3	vec3_v;
	t_vec3	pc;
	double	theta;
	double	height;

	set_uv_axis(hit.elem.fig.cy.nv, &vec3_u, &vec3_v);
	pc = vsub(hit.point, hit.elem.fig.cy.c);
	theta = atan2(-1 * dot(pc, vec3_u), dot(pc, vec3_v)) + M_PI;
	height = dot(pc, hit.elem.fig.cy.nv);
	*u = theta * M_1_PI * 0.5;
	*v = fmod(height, 1);
}

void	uv_mapping_cone(double *u, double *v, t_hit hit)
{
	t_vec3	vec3_u;
	t_vec3	vec3_v;
	t_vec3	pc;
	double	theta;
	double	height;

	set_uv_axis(hit.elem.fig.con.nv, &vec3_u, &vec3_v);
	pc = vsub(hit.point, hit.elem.fig.con.c);
	theta = atan2(-1 * dot(pc, vec3_u), dot(pc, vec3_v)) + M_PI;
	height = dot(pc, hit.elem.fig.con.nv);
	*u = theta * M_1_PI * 0.5;
	*v = fmod(height, 1);
}
