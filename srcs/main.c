/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:49:55 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/26 14:58:31 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_program(void *param)
{
	param = (void *)param;
	exit(0);
	return (1);
}

void	init_scene(t_scene *scene)
{
	scene->xres = -1;
	scene->yres = -1;
	scene->cam_nb = 0;
	scene->l = NULL;
	scene->ambient_light = -1;
	scene->al_color = -1;
	scene->bgr = -1;
}

void	init_minirt(t_minirt *minirt)
{
	minirt->cam = NULL;
	minirt->figures = NULL;
	init_scene(&minirt->scene);
}

int	main(int ac, char **av)
{
	t_minirt	minirt;
	t_figures	*lst;
	t_light		*light;

	if (ac < 2 || ac > 3)
	{
		printf("Usage: %s <scene.rt>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	init_minirt(&minirt);
	parse_file(&minirt, av);
	lst = minirt.figures;
	while (minirt.cam)
	{
		printf("cam: %f %f %f , %f %f %f , %d\n", minirt.cam->o.x, minirt.cam->o.y, minirt.cam->o.z,
		   minirt.cam->nv.x, minirt.cam->nv.y, minirt.cam->nv.z, minirt.cam->fov);
		minirt.cam = minirt.cam->next;
	}
	while (lst)
	{
		if (lst->flag == SP)
			printf("sp: %f %f %f %f %d\n", lst->fig.sp.c.x, lst->fig.sp.c.y, lst->fig.sp.c.z, lst->fig.sp.r, lst->fig.sp.inside);
		else if (lst->flag == PL)
			printf("pl: %f %f %f\n", lst->fig.pl.p.x, lst->fig.pl.p.y, lst->fig.pl.p.z);
		lst = lst->next;
	}
	printf("A: %f %d\n", minirt.scene.ambient_light, minirt.scene.al_color);
	light = minirt.scene.l;
	while (light)
	{
		printf("L: %f %f %f %f %d\n", light->o.x, light->o.y, light->o.z, light->br, light->color);
		light = light->next;
	}
	return (0);
}
