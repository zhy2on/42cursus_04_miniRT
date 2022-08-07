/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:11:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/07 17:24:00 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_plane(t_scene *scene, char **str)
{
	t_figures	*new;

	new = get_figures_node(PL);
	next(str);
	new->fig.pl.p = parse_vec3(str);
	new->fig.pl.nv = normalize(parse_vec3(str));
	new->specular = stof(str);
	new->refl_idx = stof(str);
	new->refr_idx = stof(str);
	new->texture = stof(str);
	if (new->texture == 2)
		new->wavelength = stof(str);
	new->clr = parse_color(str);
	check_figures_setting(*new);
	push_figures_node(scene, new);
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
	check_figures_setting(*new);
	push_figures_node(scene, new);
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
	check_figures_setting(*new);
	push_figures_node(scene, new);
}

void	parse_cone(t_scene *scene, char **str)
{
	t_figures	*new;

	new = get_figures_node(CON);
	next(str);
	new->fig.con.c = parse_vec3(str);
	new->fig.con.nv = normalize(parse_vec3(str));
	new->fig.con.theta = stof(str);
	new->fig.con.height = stof(str);
	new->specular = stof(str);
	new->refl_idx = stof(str);
	new->refr_idx = stof(str);
	new->texture = stof(str);
	if (new->texture == 2)
		new->wavelength = stof(str);
	new->clr = parse_color(str);
	check_figures_setting(*new);
	push_figures_node(scene, new);
}
