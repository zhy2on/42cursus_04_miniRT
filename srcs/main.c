/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:49:55 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 17:22:10 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_program(void *param)
{
	param = (void *)param;
	exit(0);
	return (1);
}

int	main(int ac, char **av)
{
	t_minirt	minirt;
	t_data		data;
	t_figures 	*lst;
	t_light		*light;

	if (ac < 2 || ac > 3)
	{
		printf("Usage: %s <scene.rt>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	lst = NULL;
	minirt.cam = NULL;
	init_scene(&minirt.scene);
	parse_file(&minirt, &data, &lst, av);
	while (minirt.cam)
	{
		printf("cam: %f %f %f , %f %f %f , %d\n", minirt.cam->o.e[0], minirt.cam->o.e[1], minirt.cam->o.e[2],
		   minirt.cam->nv.e[0], minirt.cam->nv.e[1], minirt.cam->nv.e[2], minirt.cam->fov);
		minirt.cam = minirt.cam->next;
	}
	while (lst)
	{
		if (lst->flag == SP)
			printf("sp: %f %f %f %f %d\n", lst->fig.sp.c.e[0], lst->fig.sp.c.e[1], lst->fig.sp.c.e[2], lst->fig.sp.r, lst->fig.sp.inside);
		else if (lst->flag == PL)
			printf("pl: %f %f %f\n", lst->fig.pl.p.e[0], lst->fig.pl.p.e[1], lst->fig.pl.p.e[2]);
		lst = lst->next;
	}
	printf("A: %f %d\n", minirt.scene.ambient_light, minirt.scene.al_color);
	light = minirt.scene.l;
	while (light)
	{
		printf("L: %f %f %f %f %d\n", light->o.e[0], light->o.e[1], light->o.e[2], light->br, light->color);
		light = light->next;
	}
	return (0);
}
