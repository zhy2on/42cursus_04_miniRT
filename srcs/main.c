/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:49:55 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/28 21:28:14 by jihoh            ###   ########.fr       */
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
	scene->al_ratio = -1;
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

	if (ac < 2 || ac > 3)
	{
		printf("Usage: %s <scene.rt>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	init_minirt(&rt);
	parse_file(&rt, av);
	init_mlx(&rt);
	render_scene(&rt, rt.scene.cam);
	mlx_loop(rt.mlx);
	return (0);
}
