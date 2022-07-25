/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:02:54 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/23 17:40:20 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient_light(t_scene *data, char **str)
{
	if (data->ambient != -1)
		exit(put_error("error: ambient light is already declared\n"));
	next(str);
	data->ambient_light = stof(str);
	if (data->ambient_light < 0 || data->ambient_light > 1)
		exit(put_error("error: ambient light is out of range\n"));
	data->al_color = parse_color(str);
}

void	init_scene(t_scene *scene)
{
	scene->xres = -1;
	scene->yres = -1;
	scene->cam_nb = 0;
	scene->*l = NULL;
	scene->ambient_light = -1;
	scene->al_color = -1;
	scene->bgr = -1;
}
