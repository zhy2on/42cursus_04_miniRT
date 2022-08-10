/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:11:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/10 17:59:45 by junyopar         ###   ########.fr       */
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
	new->clr = parse_color(str);
	check_figures_setting(*new);
	push_figures_node(scene, new);
}
