/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 06:17:56 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/12 03:02:07 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	uv_mapping_plane(double *u, double *v, t_vec3 uv_axis[2], t_hit hit)
{
	set_uv_axis(hit.nv, &uv_axis[0], &uv_axis[1]);
	*u = fmod(dot(hit.point, uv_axis[0]), 1);
	if (*u < 0)
		*u += 1;
	*v = fmod(dot(hit.point, uv_axis[1]), 1);
	if (*v < 0)
		*v += 1;
}

void	uv_mapping_sphere(double *u, double *v, t_vec3 uv_axis[2], t_hit hit)
{
	double	theta;
	double	phi;

	set_uv_axis(hit.nv, &uv_axis[0], &uv_axis[1]);
	theta = acos(-1 * hit.nv.y);
	phi = atan2(-1 * hit.nv.z, hit.nv.x) + M_PI;
	*u = phi * M_1_PI * 0.5;
	*v = theta * M_1_PI;
}

void	uv_mapping_cylinder(double *u, double*v, t_vec3 uv_axis[2], t_hit hit)
{
	t_vec3	pc;
	double	theta;
	double	height;

	set_uv_axis(hit.elem.fig.cy.nv, &uv_axis[0], &uv_axis[1]);
	pc = vsub(hit.point, hit.elem.fig.cy.c);
	theta = atan2(-1 * dot(pc, uv_axis[0]), dot(pc, uv_axis[1])) + M_PI;
	height = dot(pc, hit.elem.fig.cy.nv);
	*u = theta * M_1_PI * 0.5;
	*v = height / hit.elem.fig.cy.height;
}

void	uv_mapping_cone(double *u, double *v, t_vec3 uv_axis[2], t_hit hit)
{
	t_vec3	pc;
	double	theta;
	double	height;

	set_uv_axis(hit.elem.fig.con.nv, &uv_axis[0], &uv_axis[1]);
	pc = vsub(hit.point, hit.elem.fig.con.c);
	theta = atan2(-1 * dot(pc, uv_axis[0]), dot(pc, uv_axis[1])) + M_PI;
	height = dot(pc, hit.elem.fig.con.nv);
	*u = theta * M_1_PI * 0.5;
	*v = height / hit.elem.fig.con.height;
}
