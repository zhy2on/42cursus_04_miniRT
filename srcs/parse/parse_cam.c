/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 02:48:48 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/04 02:51:35 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam	*get_cam_node(t_p3 o, t_vec3 nv, int fov)
{
	t_cam	*cam;

	cam = ft_malloc(sizeof(t_cam));
	cam->o = o;
	cam->nv = nv;
	cam->fov = fov;
	cam->next = NULL;
	return (cam);
}

void	parse_camera(t_scene *scene, char **str)
{
	t_cam	*new;
	t_cam	*ptr;

	next(str);
	new = get_cam_node(parse_vec3(str),
			normalize(parse_vec3(str)), stof(str));
	ptr = scene->cam;
	if (!ptr)
	{
		scene->first = new;
		scene->cam = new;
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}
