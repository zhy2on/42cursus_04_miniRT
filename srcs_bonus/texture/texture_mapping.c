/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 05:25:45 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 23:48:06 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_pixel_color(t_xpm_img xpm_img, int x, int y)
{
	char	*dst;

	x = clamp(x, 0, xpm_img.w - 1);
	y = clamp(y, 0, xpm_img.h - 1);
	dst = xpm_img.addr + (y * xpm_img.size + x * (xpm_img.bpp / 8));
	return (*(unsigned int *)dst);
}

int	image_mapping(double u, double v, t_xpm_img img_map)
{
	int		u2;
	int		v2;
	int		color;

	u2 = clamp(u * img_map.w, 0, img_map.w - 1);
	v2 = clamp((1.0 - v) * img_map.h, 0, img_map.h - 1);
	color = get_pixel_color(img_map, u2, v2);
	return (color);
}

int	texture_mapping(t_hit hit)
{
	double	u;
	double	v;

	if (hit.elem.type == PL)
		uv_mapping_plane(&u, &v, hit);
	if (hit.elem.type == SP)
		uv_mapping_sphere(&u, &v, hit);
	if (hit.elem.type == CY)
		uv_mapping_cylinder(&u, &v, hit);
	if (hit.elem.type == CON)
		uv_mapping_cone(&u, &v, hit);
	if (hit.elem.tx && hit.elem.tx->img_map.ptr)
		return (image_mapping(u, v, hit.elem.tx->img_map));
	if (hit.elem.checker_w > 0)
		return (checker_board_pattern_at(u, v, hit));
	return (hit.elem.clr);
}
