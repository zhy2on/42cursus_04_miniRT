/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:13:36 by junyopar          #+#    #+#             */
/*   Updated: 2022/07/25 16:04:28 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void pares_sphere(t_figures **elem, char **str)
{
    t_figures *lst;

    ft_addnewlst_back(elem);
    lst = *elem;
    while (lst->next)
        lst = lst->next;
    lst->flag = SP;
    next(str);
    lst->fig.sp.c = parse_vec3(str);
    lst->fig.sp.r = stof(str) / 2;
	// in_range(lst->fig.sp.r, 0, INFINITY, "sphere");
	lst->specular = stoi(str);
	// in_range(lst->specular, 0, INFINITY, "sphere");
	lst->refl_idx = stof(str);
	// in_range(lst->refl_idx, 0, 1, "sphere");
	lst->refr_idx = stof(str);
	// in_range(lst->refr_idx, 0, INFINITY, "sphere");
	lst->texture = stoi(str);
	// in_range(lst->texture, 0, 5, "sphere");
	if (lst->texture == 2)
		lst->wavelength = stof(str);
	lst->color = parse_color(str);
}

void		parse_plane(t_figures **elem, char **str)
{
	t_figures	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = PL;
	next(str);
	lst->fig.pl.p = parse_vec3(str);
	lst->normal = normalize(parse_vec3(str));
	lst->specular = stoi(str);
	// in_range(lst->specular, 0, INFINITY, "plane");
	lst->refl_idx = stof(str);
	// in_range(lst->refl_idx, 0, 1, "plane");
	lst->refr_idx = stof(str);
	in_range(lst->refr_idx, 0, INFINITY, "plane");
	lst->texture = stoi(str);
	// in_range(lst->texture, 0, 5, "plane");
	if (lst->texture == 2)
		lst->wavelength = stof(str);
	lst->color = parse_color(str);
}