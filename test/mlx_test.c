/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:22:34 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/26 16:22:36 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	init_mlx(t_minirt *rt)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
		put_error("fail to init mlx\n");
	printf("start minirt\n");
	// mlx_get_screen_size(rt->mlx, &rt->win_w, &rt->win_h);
	// if (rt->scene.xres < rt->win_w)
	// 	rt->win_w = rt->scene.xres;
	// if (rt->scene.yres < rt->win_h)
	// 	rt->win_h = rt->scene.yres;
	rt->win = mlx_new_window(rt->mlx, rt->win_w, rt->win_h, "minirt");
	mlx_hook(rt->win, DESTROYNOTIFY, 1L << 17, exit_program, 0);
	mlx_hook(rt->win, ON_KEYDOWN, 1L << 0, key_hook, &rt);
}

void	init_cam(t_cam *cam)
{
	cam->aspect_ratio = 16.0 / 9.0;
	cam->vport_h = 2.0;
	cam->vport_w = cam->aspect_ratio * cam->vport_h;
	cam->focal_len = 1.0;
	cam->origin = get_vec3(0, 0, 0);
	cam->horizontal = get_vec3(cam->vport_w, 0, 0);
	cam->vertical = get_vec3(0, cam->vport_h, 0);
	cam->l_l_c = vsub(cam->origin, vdiv_n(cam->horizontal, 2));
	cam->l_l_c = vsub(cam->l_l_c, vdiv_n(cam->vertical, 2));
	cam->l_l_c = vsub(cam->l_l_c, get_vec3(0, 0, cam->focal_len));
}

void	init_minirt(t_minirt *rt)
{
	rt->size[0] = 800;
	rt->size[1] = 450;
	rt->mlx_ptr = mlx_init();
	rt->win_ptr = mlx_new_window(rt->mlx_ptr,
			rt->size[0], rt->size[1], "minirt");
	rt->data.img = mlx_new_image(rt->mlx_ptr,
			rt->size[0], rt->size[1]);
	rt->data.buff = mlx_get_data_addr(rt->data.img, &rt->data.bpp,
			&rt->data.bpl, &rt->data.endian);
	init_cam(&rt->cam);
}

int	key_hook(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_ESC)
		exit(0);
	return (1);
}

int	main(void)
{
	t_minirt	minirt;

	init_minirt(&minirt);
	mlx_hook(minirt.win_ptr, DESTROYNOTIFY, 1L << 17, exit_program, 0);
	mlx_hook(minirt.win_ptr, ON_KEYDOWN, 1L << 0, key_hook, &minirt);
	mlx_loop(minirt.mlx_ptr);
	return (0);
}
