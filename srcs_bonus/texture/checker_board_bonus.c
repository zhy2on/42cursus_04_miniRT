/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:04:08 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/10 14:53:53 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	uv_pattern_at_plane(t_hit hit)
{
	t_vec3	vec3_uv[2];
	double	u;
	double	v;

	set_uv_axis(hit.nv, &vec3_uv[0], &vec3_uv[1]);
	u = fmod(dot(hit.point, vec3_uv[0]), 1);
	v = fmod(dot(hit.point, vec3_uv[1]), 1);
	return (uv_pattern_at(u, v, hit));
}

int	uv_pattern_at_sphere(t_hit hit)
{
	t_vec3	vec3_uv[2];
	double	theta;
	double	phi;
	double	u;
	double	v;

	set_uv_axis(hit.nv, &vec3_uv[0], &vec3_uv[1]);
	theta = acos(-1 * hit.nv.y);
	phi = atan2(-1 * hit.nv.z, hit.nv.x) + M_PI;
	u = phi * M_1_PI * 0.5;
	v = theta * M_1_PI;
	return (uv_pattern_at(u, v, hit));
}

int	uv_pattern_at_cylinder(t_hit hit)
{
	t_vec3	vec3_uv[2];
	t_vec3	pc;
	double	theta;
	double	height;
	double	uv[2];

	set_uv_axis(hit.elem.fig.cy.nv, &vec3_uv[0], &vec3_uv[1]);
	pc = vsub(hit.point, hit.elem.fig.cy.c);
	theta = atan2(-1 * dot(pc, vec3_uv[0]), dot(pc, vec3_uv[1])) + M_PI;
	height = dot(pc, hit.elem.fig.cy.nv);
	uv[0] = theta * M_1_PI * 0.5;
	uv[1] = fmod(height, 1);
	return (uv_pattern_at(uv[0], uv[1], hit));
}

int	uv_pattern_at_cone(t_hit hit)
{
	t_vec3	vec3_uv[2];
	t_vec3	pc;
	double	theta;
	double	height;
	double	uv[2];

	set_uv_axis(hit.elem.fig.con.nv, &vec3_uv[0], &vec3_uv[1]);
	pc = vsub(hit.point, hit.elem.fig.con.c);
	theta = atan2(-1 * dot(pc, vec3_uv[0]), dot(pc, vec3_uv[1])) + M_PI;
	height = dot(pc, hit.elem.fig.con.nv);
	uv[0] = theta * M_1_PI * 0.5;
	uv[1] = fmod(height, 1);
	return (uv_pattern_at(uv[0], uv[1], hit));
}

int	checker_board(t_hit hit)
{
	if (hit.elem.type == PL)
		return (uv_pattern_at_plane(hit));
	if (hit.elem.type == SP)
		return (uv_pattern_at_sphere(hit));
	if (hit.elem.type == CY)
		return (uv_pattern_at_cylinder(hit));
	if (hit.elem.type == CON)
		return (uv_pattern_at_cone(hit));
	return (hit.elem.clr);
}
