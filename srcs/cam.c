/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:41:27 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/26 14:52:38 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_cam_info(t_scene *scene, t_cam *cam)
{
	double	vp[2];
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;

	while (cam)
	{
		vp[0] = 2 * tan(cam->fov / 2);
		vp[1] = vp[0] * (double)scene->resol.y / scene->resol.x;
		w = normalize(v_scale(cam->normal, -1));
		u = v_cross(gen_coord(0, 1, 0), w);
		v = v_cross(w, u);
		cam->hor = v_scale(u, vp[0]);
		cam->ver = v_scale(v, vp[1]);
		cam->llc = v_sub(cam->point, v_scale(cam->hor, 0.5));
		cam->llc = v_sub(cam->llc, v_scale(cam->ver, 0.5));
		cam->llc = v_sub(cam->llc, w);
		cam = cam->next;
	}
}
