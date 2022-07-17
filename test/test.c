/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:44:51 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/17 18:46:01 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct s_vec3
{
	double	e[3];
}				t_vec3;

typedef t_vec3	t_p3;

t_vec3	get_vec3(double e0, double e1, double e2)
{
	t_vec3	ret;

	ret.e[0] = e0;
	ret.e[1] = e1;
	ret.e[2] = e2;
	return (ret);
}

int	main(void)
{
	t_p3	p;

	p = get_vec3(1, 2, 3);
	printf("%f %f %f\n", p.e[0], p.e[1], p.e[2]);
}
