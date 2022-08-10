/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:39:36 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/08 02:32:10 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cscale(int color, double d)
{
	int		rgb[3];

	rgb[0] = clamp(d * (color >> 0x10), 0, 0xFF);
	rgb[1] = clamp(d * ((color >> 0x08) & 0xFF), 0, 0xFF);
	rgb[2] = clamp(d * (color & 0xFF), 0, 0xFF);
	return ((rgb[0] << 0x10) | (rgb[1] << 0x08) | rgb[2]);
}

int	cprod(int c1, int c2)
{
	int	rgb[3];

	rgb[0] = (((double)(c1 >> 0x10) / 0xFF)
			* ((double)(c2 >> 0x10) / 0xFF)) * 0xFF;
	rgb[1] = (((double)((c1 >> 0x08) & 0xFF) / 0xFF)
			* ((double)((c2 >> 0x08) & 0xFF) / 0xFF)) * 0xFF;
	rgb[2] = (((double)(c1 & 0xFF) / 0xFF)
			* ((double)(c2 & 0xFF) / 0xFF)) * 0xFF;
	return ((rgb[0] << 0x10) | (rgb[1] << 0x08) | rgb[2]);
}

int	cadd(int c1, int c2)
{
	int		r;
	int		g;
	int		b;

	r = clamp((c1 >> 0x10) + (c2 >> 0x10), 0, 0xFF);
	g = clamp((c1 >> 0x08 & 0xFF) + (c2 >> 0x08 & 0xFF), 0, 0xFF);
	b = clamp((c1 & 0xFF) + (c2 & 0xFF), 0, 0xFF);
	return ((r << 0x10) | (g << 0x08) | b);
}
