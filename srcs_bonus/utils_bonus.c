/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:31:14 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 01:08:32 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_error(char *str, char *error_line)
{
	if (error_line)
	{
		ft_putstr_fd(YELLOW, 2);
		ft_putstr_fd("stop at: ", 2);
		ft_putendl_fd(error_line, 2);
	}
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	*ft_malloc(unsigned int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		put_error("malloc failed", NULL);
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

void	set_uv_axis(t_vec3 w, t_vec3 *u, t_vec3	*v)
{
	w = normalize(w);
	if (w.y == 1 || w.y == -1)
		*u = create_vec3(w.y, 0, 0);
	else
		*u = cross(create_vec3(0, 1, 0), w);
	*v = cross(w, *u);
}
