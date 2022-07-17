/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:49:55 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/17 18:52:24 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cam(t_cam *cam)
{
	cam->aspect_ratio = 16.0 / 9.0;
	cam->vport_h = 2.0;
	cam->vport_w = cam->aspect_ratio * cam->vport_h;
	cam->focal_len = 1.0;
	cam->origin = get_vec3(0, 0, 0);
	cam->horizontal = get_vec3(cam->vport_w, 0, 0);
	cam->vertical = get_vec3(0, cam->vport_h, 0);
	cam->l_l_c = vsub(cam->origin, vdiv_n(cam->horizontal, 2));
	cam->l_l_c = vsub(cam->l_l_c, vdiv_n(cam->vertical, 2));
	cam->l_l_c = vsub(cam->l_l_c, get_vec3(0, 0, cam->focal_len));
}

int	main(void)
{
	t_cam	cam;

	init_cam(&cam);
	printf("%f %f %f\n", cam.l_l_c.e[0], cam.l_l_c.e[1], cam.l_l_c.e[2]);
	return (0);
}
