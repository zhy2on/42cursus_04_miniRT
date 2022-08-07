/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:31:14 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/07 16:55:46 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_error(char *str)
{
	write(2, "error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

void	*ft_malloc(unsigned int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		put_error("malloc failed");
	return (ptr);
}

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

t_p3	get_hit_point(t_ray ray)
{
	return (vadd(ray.o, vscale(ray.dir, ray.hit.time)));
}

void	solve_quadratic(double a, double b, double c, double root[2])
{
	double	sqrt_disc;
	double	tmp;

	sqrt_disc = sqrt(pow(b, 2) - 4 * a * c);
	root[0] = (-b - sqrt_disc) / (2 * a);
	if (root[0] <= EPSILON)
		root[0] = INFINITY;
	root[1] = (-b + sqrt_disc) / (2 * a);
	if (root[1] <= EPSILON)
		root[1] = INFINITY;
	if (root[1] < root[0])
	{
		tmp = root[1];
		root[1] = root[0];
		root[0] = tmp;
	}
}
