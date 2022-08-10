/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:26:47 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 01:02:36 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	next(char **pstr)
{
	while (**pstr == 32 || **pstr == 9)
		(*pstr)++;
}

void	comma(char **pstr, char *error_line)
{
	if (**pstr != ',')
		put_error("bad formatted", error_line);
	(*pstr)++;
}

t_vec3	parse_vec3(char **pstr, char *error_line)
{
	t_vec3	vec;

	vec.x = stof(pstr);
	comma(pstr, error_line);
	vec.y = stof(pstr);
	comma(pstr, error_line);
	vec.z = stof(pstr);
	next(pstr);
	return (vec);
}

double	stof(char **pstr)
{
	int		w;
	double	d;
	int		neg;

	w = 0;
	neg = 1;
	if (**pstr == '-' && *((*pstr)++))
		neg = -1;
	while (ft_isdigit(**pstr))
		w = w * 10 + (*((*pstr)++) - '0');
	if (**pstr == '.')
		(*pstr)++;
	d = 0.0;
	while (ft_isdigit(**pstr))
		d = d * 10 + (*((*pstr)++) - '0');
	while (d >= 1)
		d /= 10;
	d += w;
	next(pstr);
	return (d * neg);
}

int	parse_color(char **pstr, char *error_line)
{
	int	r;
	int	g;
	int	b;

	r = stof(pstr);
	if (r < 0 || r > 255)
		put_error("out of color range", error_line);
	r <<= 0x10;
	comma(pstr, error_line);
	g = stof(pstr);
	if (g < 0 || g > 255)
		put_error("out of color range", error_line);
	g <<= 0x8;
	comma(pstr, error_line);
	b = stof(pstr);
	if (b < 0 || b > 255)
		put_error("out of color range", error_line);
	return (r | g | b);
}
