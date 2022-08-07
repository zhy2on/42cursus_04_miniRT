/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:00:28 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/08 01:50:46 by jihoh            ###   ########.fr       */
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

void	check_figures_setting2(t_figures elem)
{
	if (elem.type == CY)
	{
		if (elem.fig.cy.height < 0 || elem.fig.cy.height > INFINITY)
			put_error("cylinder height is out of range");
		if (elem.fig.cy.r < 0 || elem.fig.cy.r > INFINITY)
			put_error("cylinder diameter is out of range");
	}
	if (elem.type == CON)
	{
		if (elem.fig.con.height < 0 || elem.fig.con.height > INFINITY)
			put_error("cone height is out of range");
		if (elem.fig.con.theta < 0 || elem.fig.con.theta >= 180)
			put_error("cone theta is out of range");
	}
}

void	check_figures_setting(t_figures elem)
{
	if (elem.specular < 0 || elem.specular > 1250)
		put_error("specular power is out of range");
	if (elem.checker_w != 0 && elem.checker_h != 0)
	{
		if (elem.checker_w < 0)
			put_error("checker board width is out of range");
		if (elem.checker_h < 0)
			put_error("checker board height is out of range");
	}
	if (elem.type == SP)
	{
		if (elem.fig.sp.r < 0 || elem.fig.sp.r > INFINITY)
			put_error("sphere diameter is out of range");
	}
	check_figures_setting2(elem);
}

void	push_figures_node(t_scene *scene, t_figures *new)
{
	if (!scene->figures)
		scene->figures = new;
	else
	{
		new->next = scene->figures;
		scene->figures = new;
	}
}
