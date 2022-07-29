/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:49:55 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/30 04:18:35 by jihoh            ###   ########.fr       */
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
	scene->al_br = -1;
	scene->al_clr = -1;
	scene->bgr = -1;
}

void	init_minirt(t_minirt *rt)
{
	rt->save = 0;
	rt->mlx = NULL;
	rt->win = NULL;
	init_scene(&rt->scene);
}

int	key_hook(int keycode, t_minirt *rt)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode != KEY_SPACE)
		return (0);
	rt->scene.cam = rt->scene.cam->next;
	render_scene(rt, rt->scene.cam);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->scene.cam->img.ptr, 0, 0);
	return (1);
}

void	set_mlx(t_minirt *rt)
{
	rt->save = 0;
	rt->mlx = mlx_init();
	if (!rt->mlx)
		put_error("fail to init mlx\n");
	printf("start minirt\n");
	rt->win = mlx_new_window(rt->mlx, rt->scene.xres, rt->scene.yres, "");
	mlx_hook(rt->win, DESTROYNOTIFY, 1L << 17, exit_program, 0);
	mlx_hook(rt->win, ON_KEYDOWN, 1L << 0, key_hook, rt);
}

int	main(int ac, char **av)
{
	t_minirt	rt;

	if (ac < 2 || ac > 3)
	{
		printf("Usage: %s <scene.rt>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	init_minirt(&rt);
	parse_file(&rt, av);
	set_mlx(&rt);
	render_scene(&rt, rt.scene.cam);
	mlx_loop(rt.mlx);
	return (0);
}
