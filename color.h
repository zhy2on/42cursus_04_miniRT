/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 01:29:23 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/15 02:01:47 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdio.h>
# include "utils.h"
# include "vec3.h"

/*
** Divide the color by the number of samples.
** Write the translated [0,255] value of each color component.
*/
void	write_color(t_vec3 pixel_color, int samples_per_pixel)
{
	double	r;
	double	g;
	double	b;
	double	scale;

	scale = 1.0 / samples_per_pixel;
	r = pixel_color.e[0] * scale;
	g = pixel_color.e[1] * scale;
	b = pixel_color.e[2] * scale;
	printf("%d %d %d\n", 256 * clamp(r, 0.0, 0.999),
		256 * clamp(g, 0.0, 0.999), 256 * clamp(b, 0.0, 0.999));
}

t_vec3	set_color(double r, double g, double b)
{
	t_vec3	ret;

	ret.e[0] = r;
	ret.e[1] = g;
	ret.e[2] = b;
	return (ret);
}

#endif