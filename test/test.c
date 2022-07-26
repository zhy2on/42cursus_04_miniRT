/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:44:51 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/26 17:20:25 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct s_vec3
{
	double	e[3];
}				t_vec3;

typedef t_vec3	t_p3;

t_vec3	create_vec3(double e0, double e1, double e2)
{
	t_vec3	ret;

	ret.x = e0;
	ret.y = e1;
	ret.z = e2;
	return (ret);
}

int	main(void)
{
	t_p3	p;

	p = create_vec3(1, 2, 3);
	printf("%f %f %f\n", p.x, p.y, p.z);
}
