/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:02:54 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 14:33:19 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient_light(t_scene *scene, char **str)
{
	if (scene->ambient_light != -1)
		exit(put_error("ambient light is already declared\n"));
	next(str);
	scene->ambient_light = stof(str);
	if (scene->ambient_light < 0 || scene->ambient_light > 1)
		exit(put_error("ambient light ratio is out of range\n"));
	scene->al_color = parse_color(str);
}

void	init_scene(t_scene *scene)
{
	scene->xres = -1;
	scene->yres = -1;
	scene->cam_nb = 0;
	scene->l = NULL;
	scene->ambient_light = -1;
	scene->al_color = -1;
	scene->bgr = -1;
}
