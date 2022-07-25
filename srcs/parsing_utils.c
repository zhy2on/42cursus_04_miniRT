/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:26:47 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 16:22:17 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	next(char **str)
{
	while (**str == 32 || **str == 9)
		(*str)++;
}

void comma(char **str)
{
	if (**str != ',')
		put_error("camera x,y,z arguments bad formatted\n");
	(*str)++;
}

t_vec3 parse_vec3(char **str)
{
	t_vec3 vec;
	
	vec.e[0] = stof(str);
	comma(str);
	vec.e[1] = stof(str);
	comma(str);
	vec.e[2] = stof(str);
	next(str);
	return (vec);
}

double	stof(char **str)
{
	int		w;
	double	d;
	int		neg;

	w = 0;
	neg = 1;
	if (**str == '-' && *((*str)++))
		neg = -1;
	while (ft_isdigit(**str))
		w = w * 10 + (*((*str)++) - '0');
	if (**str == '.')
		(*str)++;
	d = 0.0;
	while (ft_isdigit(**str))
		d = d * 10 + (*((*str)++) - '0');
	while (d >= 1)
		d /= 10;
	d += w;
	next(str);
	return (d * neg);
}

int	stoi(char **str)
{
	int	i;
	int	neg;

	i = 0;
	neg = 1;
	if (**str == '-' && *((*str)++))
		neg = -1;
	while (ft_isdigit(**str))
		i = i * 10 + (*((*str)++) - '0');
	next(str);
	return (i * neg);
}

int	parse_color(char **str)
{
	int	r;
	int	g;
	int	b;

	r = stoi(str);
	if (r < 0 || r > 255)
		exit(put_error("error: out of color range\n"));
	r <<= 16;
	comma(str);
	g = stoi(str);
	if (g < 0 || g > 255)
		exit(put_error("error: out of color range\n"));
	g <<= 8;
	comma(str);
	b = stoi(str);
	if (b < 0 || b > 255)
		exit(put_error("error: out of color range\n"));
	return (r | g | b);
}

