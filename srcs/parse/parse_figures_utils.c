/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:00:28 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 00:19:04 by jihoh            ###   ########.fr       */
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

void	check_figures_setting(t_figures elem, char *error_line)
{
	if (elem.type == SP)
	{
		if (elem.fig.sp.r < 0 || elem.fig.sp.r > INFINITY)
			put_error("sphere diameter is out of range", error_line);
	}
	if (elem.type == CY)
	{
		if (elem.fig.cy.height < 0 || elem.fig.cy.height > INFINITY)
			put_error("cylinder height is out of range", error_line);
		if (elem.fig.cy.r < 0 || elem.fig.cy.r > INFINITY)
			put_error("cylinder diameter is out of range", error_line);
	}
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
