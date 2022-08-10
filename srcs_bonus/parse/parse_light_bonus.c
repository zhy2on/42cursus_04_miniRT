/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:02:54 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 03:53:11 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	parse_ambient_light(t_scene *scene, char **pstr, char *error_line)
{
	if (scene->al_br != -1)
		put_error("ambient lighting declared multiple times", error_line);
	next(pstr);
	scene->al_br = stof(pstr);
	if (scene->al_br < 0 || scene->al_br > 1)
		put_error("ambient lighting ratio is out of range", error_line);
	scene->al_clr = parse_color(pstr, error_line);
}

t_light	*get_light_node(t_p3 o, double br, int clr)
{
	t_light	*light;

	light = ft_malloc(sizeof(t_light));
	light->o = o;
	light->br = br;
	light->clr = clr;
	light->next = NULL;
	return (light);
}

void	parse_light(t_scene *scene, char **pstr, char *error_line)
{
	t_light	*new;

	next(pstr);
	new = get_light_node(parse_vec3(pstr, error_line),
			stof(pstr), parse_color(pstr, error_line));
	if (new->br < 0 || new->br > 1)
		put_error("lighting ratio is out of range", error_line);
	if (!scene->light)
		scene->light = new;
	else
	{
		new->next = scene->light;
		scene->light = new;
	}
}
