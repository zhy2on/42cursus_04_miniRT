/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 01:42:23 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/15 02:11:48 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
** Returns a random real in [0,1).
*/
double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

/*
** Returns a random real in [min,max).
*/
double	random_double(double min, double max)
{
	return (min + (max - min) * random_double());
}

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

#endif