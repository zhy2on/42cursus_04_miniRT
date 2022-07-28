/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:41:27 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/28 18:14:00 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_cam(t_scene *scene, t_cam *cam)
{
	double	vp[2];
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;
	// t_vec3	tmp;

	while (cam)
	{
		vp[0] = 2 * tan(cam->fov / 2);
		vp[1] = vp[0] * (double)scene->yres / scene->xres;
		w = normalize(vscale(cam->nv, -1));
		u = cross(create_vec3(0, 1, 0), w);
		v = cross(w, u);
		// w = normalize(vscale(cam->nv, -1));
		// u = cross(create_vec3(0, 1, 0), w);
		// v = cross(w, u);
		// tmp = v;
		// v = w;
		// w = u;
		// u = tmp;
		cam->hor = vscale(u, -vp[0]);
		cam->ver = vscale(v, -vp[1]);
		cam->llc = vsub(cam->o, vscale(cam->hor, 0.5));
		cam->llc = vsub(cam->llc, vscale(cam->ver, 0.5));
		cam->llc = vsub(cam->llc, w);
		cam = cam->next;
	}
}
