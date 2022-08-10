/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:11:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 00:31:52 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_plane(t_scene *scene, char **pstr, char *error_line)
{
	t_figures	*new;

	new = get_figures_node(PL);
	next(pstr);
	new->fig.pl.p = parse_vec3(pstr, error_line);
	new->fig.pl.nv = normalize(parse_vec3(pstr, error_line));
	new->clr = parse_color(pstr, error_line);
	check_figures_setting(*new, error_line);
	push_figures_node(scene, new);
}

void	parse_sphere(t_scene *scene, char **pstr, char *error_line)
{
	t_figures	*new;

	new = get_figures_node(SP);
	next(pstr);
	new->fig.sp.c = parse_vec3(pstr, error_line);
	new->fig.sp.r = stof(pstr) / 2;
	new->clr = parse_color(pstr, error_line);
	check_figures_setting(*new, error_line);
	push_figures_node(scene, new);
}

void	parse_cylinder(t_scene *scene, char **pstr, char *error_line)
{
	t_figures	*new;

	new = get_figures_node(CY);
	next(pstr);
	new->fig.cy.c = parse_vec3(pstr, error_line);
	new->fig.cy.nv = normalize(parse_vec3(pstr, error_line));
	new->fig.cy.r = stof(pstr) / 2;
	new->fig.cy.height = stof(pstr);
	new->clr = parse_color(pstr, error_line);
	check_figures_setting(*new, error_line);
	push_figures_node(scene, new);
}
