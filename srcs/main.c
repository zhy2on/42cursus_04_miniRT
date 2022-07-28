/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:49:55 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/28 14:48:41 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_program(void *param)
{
	(void)param;
	exit(0);
	return (1);
}

void	init_scene(t_scene *scene)
{
	scene->cam = NULL;
	scene->figures = NULL;
	scene->light = NULL;
	scene->xres = -1;
	scene->yres = -1;
	scene->cam_nb = 0;
	scene->ambient_light = -1;
	scene->al_color = -1;
	scene->bgr = -1;
}

void	init_minirt(t_minirt *rt)
{
	rt->save = 0;
	rt->mlx = NULL;
	rt->win = NULL;
	rt->win_w = -1;
	rt->win_h = -1;
	init_scene(&rt->scene);
}

int	key_hook(int keycode, t_minirt *rt)
{
	(void)rt;
	if (keycode == KEY_ESC)
		exit(0);
	return (1);
}

void	init_mlx(t_minirt *rt)
{
	rt->save = 0;
	rt->mlx = mlx_init();
	if (!rt->mlx)
		put_error("fail to init mlx\n");
	printf("start minirt\n");
	rt->win = mlx_new_window(rt->mlx, rt->win_w, rt->win_h, "minirt");
	mlx_hook(rt->win, DESTROYNOTIFY, 1L << 17, exit_program, 0);
	mlx_hook(rt->win, ON_KEYDOWN, 1L << 0, key_hook, &rt);
}


int	main(int ac, char **av)
{
	t_minirt	rt;
	t_figures	*figures;
	t_cam		*cam;

	if (ac < 2 || ac > 3)
	{
		printf("Usage: %s <scene.rt>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	init_minirt(&rt);
	parse_file(&rt, av);
	cam = rt.scene.cam;
	while (cam)
	{
		printf("cam: %f %f %f , %f %f %f , %d\n", cam->o.x, cam->o.y, cam->o.z,
			cam->nv.x, cam->nv.y, cam->nv.z, cam->fov);
		printf("llc: %f %f %f\n", cam->llc.x, cam->llc.y, cam->llc.z);
		cam = cam->next;
	}
	figures = rt.scene.figures;
	while (figures)
	{
		if (figures->flag == SP)
			printf("sp: %f %f %f %f %d\n",
				figures->fig.sp.c.x, figures->fig.sp.c.y, figures->fig.sp.c.z,
				figures->fig.sp.r, figures->fig.sp.inside);
		else if (figures->flag == PL)
			printf("pl: %f %f %f\n",
				figures->fig.pl.p.x, figures->fig.pl.p.y, figures->fig.pl.p.z);
		figures = figures->next;
	}
	init_mlx(&rt);
	render_scene(&rt, rt.scene.cam);
	mlx_loop(rt.mlx);
	return (0);
}
