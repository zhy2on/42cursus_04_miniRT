/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:04:08 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/08 23:39:12 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	complementary_color(int clr)
{
	int		r;
	int		g;
	int		b;

	r = 0xFF - (clr >> 0x10);
	g = 0xFF - (clr >> 0x08 & 0xFF);
	b = 0xFF - (clr & 0xFF);
	return ((r << 0x10) | (g << 0x08) | b);
}

int	uv_pattern_at(double u, double v, t_hit hit)
{
	int	u2;
	int	v2;
	int	res;

	u2 = u * hit.elem.checker_w;
	v2 = v * hit.elem.checker_h;
	res = (u2 + v2) % 2;
	if (res)
		return (hit.elem.clr);
	else
		return (complementary_color(hit.elem.clr));
}

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

int	checker_board(t_hit hit)
{
	if (hit.elem.type == PL)
		return (uv_pattern_at_plane(hit));
	if (hit.elem.type == SP)
		return (uv_pattern_at_sphere(hit));
	return (hit.elem.clr);
}
