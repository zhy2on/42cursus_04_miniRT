/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:02:54 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/10 18:18:27 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient_light(t_scene *scene, char **str)
{
	if (scene->al_br != -1)
		put_error("ambient lighting declared multiple times", NULL);
	next(str);
	scene->al_br = stof(str);
	if (scene->al_br < 0 || scene->al_br > 1)
		put_error("ambient lighting ratio is out of range", NULL);
	scene->al_clr = parse_color(str);
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

void	parse_light(t_scene *scene, char **str)
{
	t_light	*new;

	next(str);
	new = get_light_node(parse_vec3(str), stof(str), parse_color(str));
	if (new->br < 0 || new->br > 1)
		put_error("lighting ratio is out of range", NULL);
	if (!scene->light)
		scene->light = new;
	else
		put_error("light is already declared", NULL);
}
