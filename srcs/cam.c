/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:41:27 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/30 03:39:00 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_cam(t_scene *scene, t_cam *cam)
{
	double	vp[2];
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;
	int		i;

	i = 0;
	while (i++ < scene->cam_nb)
	{
		vp[0] = 2 * tan(cam->fov / 2);
		vp[1] = vp[0] * (double)scene->yres / scene->xres;
		w = normalize(vscale(cam->nv, -1));
		if (w.y == 1 || w.y == -1)
			u = create_vec3(w.y, 0, 0);
		else
			u = cross(create_vec3(0, 1, 0), w);
		v = cross(w, u);
		cam->hor = vscale(u, vp[0]);
		cam->ver = vscale(v, vp[1]);
		cam->llc = vsub(cam->o, vscale(cam->hor, 0.5));
		cam->llc = vsub(cam->llc, vscale(cam->ver, 0.5));
		cam->llc = vsub(cam->llc, w);
		cam = cam->next;
	}
}
