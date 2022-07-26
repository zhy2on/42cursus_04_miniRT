/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:13:36 by junyopar          #+#    #+#             */
/*   Updated: 2022/07/26 16:22:00 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_figures	*get_figures_node(int flag)
{
	t_figures	*figures;

	figures = ft_malloc(sizeof(t_figures));
	figures->flag = flag;
	figures->next = NULL;
	return (figures);
}

void	parse_sphere(t_minirt *rt, char **str)
{
	t_figures	*new;

	new = get_figures_node(SP);
	next(str);
	new->fig.sp.c = parse_vec3(str);
	new->fig.sp.r = stof(str) / 2;
	new->specular = stoi(str);
	new->refl_idx = stof(str);
	new->refr_idx = stof(str);
	new->texture = stoi(str);
	if (new->texture == 2)
		new->wavelength = stof(str);
	new->color = parse_color(str);
	if (new->fig.sp.r < 0 || new->fig.sp.r > INFINITY
		|| new->specular < 0 || new->specular > INFINITY
		|| new->refl_idx < 0 || new->refl_idx > 1
		|| new->refr_idx < 0 || new->refr_idx > INFINITY
		|| new->texture < 0 || new->texture > 5)
		put_error("sphere set is out of range\n");
	add_figures_back(rt, new);
}

void	parse_plane(t_minirt *rt, char **str)
{
	t_figures	*new;

	new = get_figures_node(PL);
	next(str);
	new->fig.pl.p = parse_vec3(str);
	new->normal = normalize(parse_vec3(str));
	new->specular = stoi(str);
	new->refl_idx = stof(str);
	new->refr_idx = stof(str);
	new->texture = stoi(str);
	if (new->texture == 2)
		new->wavelength = stof(str);
	new->color = parse_color(str);
	if (new->specular < 0 || new->specular > INFINITY
		|| new->refl_idx < 0 || new->refl_idx > 1
		|| new->refr_idx < 0 || new->refr_idx > INFINITY)
		put_error("plane set is out of range\n");
	add_figures_back(rt, new);
}

void	add_figures_back(t_minirt *rt, t_figures *new)
{
	t_figures	*ptr;

	ptr = rt->figures;
	if (!ptr)
		rt->figures = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}
