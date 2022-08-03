/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:31:14 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/04 02:11:10 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_error(char *str)
{
	write(2, "error: ", 7);
	write(2, str, ft_strlen(str));
	exit(1);
}

void	*ft_malloc(unsigned int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		put_error("malloc failed\n");
	return (ptr);
}

double	time_clamp(double x)
{
	if (x <= EPSILON)
		return (INFINITY);
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
	root[0] = time_clamp((-b - sqrt_disc) / (2 * a));
	root[1] = time_clamp((-b + sqrt_disc) / (2 * a));
	if (root[1] < root[0])
	{
		tmp = root[1];
		root[1] = root[0];
		root[0] = tmp;
	}
}
