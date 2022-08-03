/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:24:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/04 02:20:11 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	create_vec3(double x, double y, double z)
{
	t_vec3	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec3	vadd(t_vec3 u, t_vec3 v)
{
	return (create_vec3(u.x + v.x, u.y + v.y, u.z + v.z));
}

t_vec3	vsub(t_vec3 u, t_vec3 v)
{
	return (create_vec3(u.x - v.x, u.y - v.y, u.z - v.z));
}

t_vec3	vscale(t_vec3 u, double n)
{
	return (create_vec3(u.x * n, u.y * n, u.z * n));
}
