/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:04:08 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/08 03:01:55 by jihoh            ###   ########.fr       */
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
	t_vec3	horizontal;
	t_vec3	vertical;
	double	u;
	double	v;

	if (hit.nv.y == 1 || hit.nv.y == -1)
		horizontal = create_vec3(hit.nv.y, 0, 0);
	else
		horizontal = cross(create_vec3(0, 1, 0), hit.nv);
	vertical = cross(hit.nv, horizontal);
	u = fmod(dot(hit.point, horizontal), 1);
	v = fmod(dot(hit.point, vertical), 1);
	return (uv_pattern_at(u, v, hit));
}

int	checker_board(t_hit hit)
{
	if (hit.elem.type == PL)
		return (uv_pattern_at_plane(hit));
	return (hit.elem.clr);
}
