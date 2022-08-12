/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:49:55 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/12 20:12:49 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_program(void *param)
{
	(void)param;
	exit(0);
	return (1);
}

void	camera_move(t_scene *scene, int keycode)
{
	t_cam	*cam;

	cam = scene->cam;
	printf("%d\n", keycode);
	if (keycode == KEY_D)
		cam->o.x -= 1;
	else if (keycode == KEY_A)
		cam->o.x += 1;
	else if (keycode == KEY_W)
		cam->o.z += 1;
	else if (keycode == KEY_S)
		cam->o.z -= 1;
	else if (keycode == UARROW)
		cam->o.y -= 1;
	else if (keycode == DARROW)
		cam->o.y += 1;
	set_cam(scene, cam);
	// printf("%f, %f, %f\n", cam->o.x,cam->o.y,cam->o.z);
}

t_figures *select_object(t_minirt *rt, int x, int y)
{
	t_ray ray;
	// t_minirt rt;
	float d;

	// rt->scene.figures->type = NULL;
	d = ((float)rt->scene.xres / 2) / tan(rt->scene.cam->fov / 2);
	ray.dir = create_ray(x - (int)rt->scene.xres / 2, y - (int)rt->scene.yres / 2, d);
	ray.o = rt->scene.cam->o;
	intersect(rt,&ray);
	printf("fig type: %d\n", rt->scene.figures->type);
}
int	key_hook(int keycode, t_minirt *rt)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_SPACE)
	{
		if (!rt->scene.cam->next)
			rt->scene.cam = rt->scene.first;
		else
			rt->scene.cam = rt->scene.cam->next;
	}
	else if (keycode == KEY_D || keycode == KEY_A || keycode == KEY_W \
		|| keycode == KEY_S || keycode == UARROW || keycode == DARROW)
		camera_move(&rt->scene, keycode);
	// if (!rt->scene.cam->next)
	// 	rt->scene.cam = rt->scene.first;
	// else
	// 	rt->scene.cam = rt->scene.cam->next;
	render_scene(rt, rt->scene.cam);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->scene.cam->img.ptr, 0, 0);
	return (1);
}

void	set_mlx(t_minirt *rt, char *f_name)
{
	printf("start minirt\n");
	rt->win = mlx_new_window(rt->mlx, rt->scene.xres, rt->scene.yres, f_name);
	mlx_hook(rt->win, DESTROYNOTIFY, 1L << 17, exit_program, 0);
	mlx_hook(rt->win, ON_KEYDOWN, 1L << 0, key_hook, rt);
}

void	init_minirt(t_minirt *rt)
{
	rt->mlx = NULL;
	rt->mlx = mlx_init();
	if (!rt->mlx)
		put_error("fail to init mlx", NULL);
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
