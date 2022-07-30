/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:11:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/30 18:14:50 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_figures	*get_figures_node(int type)
{
	t_figures	*figures;

	figures = ft_malloc(sizeof(t_figures));
	figures->type = type;
	figures->next = NULL;
	return (figures);
}

void	parse_sphere(t_scene *scene, char **str)
{
	t_figures	*new;

	new = get_figures_node(SP);
	next(str);
	new->fig.sp.c = parse_vec3(str);
	new->fig.sp.r = stof(str) / 2;
	new->specular = stof(str);
	new->refl_idx = stof(str);
	new->refr_idx = stof(str);
	new->texture = stof(str);
	if (new->texture == 2)
		new->wavelength = stof(str);
	new->clr = parse_color(str);
	if (new->fig.sp.r < 0 || new->fig.sp.r > INFINITY
		|| new->specular < 0 || new->specular > INFINITY
		|| new->refl_idx < 0 || new->refl_idx > 1
		|| new->refr_idx < 0 || new->refr_idx > INFINITY
		|| new->texture < 0 || new->texture > 5)
		put_error("sphere setting is out of range\n");
	add_figures_back(scene, new);
}

void	parse_plane(t_scene *scene, char **str)
{
	t_figures	*new;

	new = get_figures_node(PL);
	next(str);
	new->fig.pl.p = parse_vec3(str);
	new->nv = normalize(parse_vec3(str));
	new->specular = stof(str);
	new->refl_idx = stof(str);
	new->refr_idx = stof(str);
	new->texture = stof(str);
	if (new->texture == 2)
		new->wavelength = stof(str);
	new->clr = parse_color(str);
	if (new->specular < 0 || new->specular > INFINITY
		|| new->refl_idx < 0 || new->refl_idx > 1
		|| new->refr_idx < 0 || new->refr_idx > INFINITY)
		put_error("plane setting is out of range\n");
	add_figures_back(scene, new);
}

void	parse_cylinder(t_scene *scene, char **str)
{
	t_figures	*new;

	new = get_figures_node(CY);
	next(str);
	new->fig.cy.c = parse_vec3(str);
	new->fig.cy.nv = normalize(parse_vec3(str));
	new->fig.cy.r = stof(str) / 2;
	new->fig.cy.height = stof(str);
	new->specular = stof(str);
	new->refl_idx = stof(str);
	new->refr_idx = stof(str);
	new->texture = stof(str);
	if (new->texture == 2)
		new->wavelength = stof(str);
	new->clr = parse_color(str);
	if (new->fig.cy.height < 0 || new->fig.cy.height > INFINITY
		|| new->fig.cy.height < 0 || new->fig.cy.height > INFINITY
		|| new->specular < 0 || new->specular > INFINITY
		|| new->refl_idx < 0 || new->refl_idx > 1
		|| new->refr_idx < 0 || new->refr_idx > INFINITY
		|| new->texture < 0 || new->texture > 5)
		put_error("cylinder setting is out of range\n");
	add_figures_back(scene, new);
}

void	add_figures_back(t_scene *scene, t_figures *new)
{
	t_figures	*ptr;

	ptr = scene->figures;
	if (!ptr)
		scene->figures = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}
