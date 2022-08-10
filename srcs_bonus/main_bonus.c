/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:49:55 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 03:56:26 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	exit_program(void *param)
{
	(void)param;
	exit(0);
	return (1);
}

int	key_hook(int keycode, t_minirt *rt)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode != KEY_SPACE)
		return (0);
	if (!rt->scene.cam->next)
		rt->scene.cam = rt->scene.first;
	else
		rt->scene.cam = rt->scene.cam->next;
	render_scene(rt, rt->scene.cam);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->scene.cam->img.ptr, 0, 0);
	return (1);
}

void	set_mlx(t_minirt *rt, char *f_name)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
		put_error("fail to init mlx", NULL);
	printf("start minirt\n");
	rt->win = mlx_new_window(rt->mlx, rt->scene.xres, rt->scene.yres, f_name);
	mlx_hook(rt->win, DESTROYNOTIFY, 1L << 17, exit_program, 0);
	mlx_hook(rt->win, ON_KEYDOWN, 1L << 0, key_hook, rt);
}

void	init_minirt(t_minirt *rt)
{
	rt->mlx = NULL;
	rt->win = NULL;
	rt->scene.first = NULL;
	rt->scene.cam = NULL;
	rt->scene.figures = NULL;
	rt->scene.light = NULL;
	rt->scene.xres = -1;
	rt->scene.yres = -1;
	rt->scene.al_br = -1;
	rt->scene.al_clr = -1;
	rt->scene.texture = NULL;
}

int	main(int ac, char **av)
{
	t_minirt	rt;

	if (ac < 2 || ac > 3)
		put_error("Usage: ./miniRT <scene.rt>", NULL);
	init_minirt(&rt);
	parse_file(&rt, av[1]);
	set_mlx(&rt, av[1]);
	render_scene(&rt, rt.scene.cam);
	mlx_loop(rt.mlx);
	return (0);
}
