/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:49:55 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/23 16:18:31 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	init_minirt(t_minirt *minirt)
{
	minirt->size[0] = 800;
	minirt->size[1] = 450;
	minirt->mlx_ptr = mlx_init();
	minirt->win_ptr = mlx_new_window(minirt->mlx_ptr,
			minirt->size[0], minirt->size[1], "minirt");
	minirt->data.img = mlx_new_image(minirt->mlx_ptr,
			minirt->size[0], minirt->size[1]);
	minirt->data.buff = mlx_get_data_addr(minirt->data.img, &minirt->data.bpp,
			&minirt->data.bpl, &minirt->data.endian);
	init_cam(&minirt->cam);
}

int	exit_program(void *param)
{
	param = (void *)param;
	exit(0);
	return (1);
}

int	key_hook(int keycode, t_minirt *minirt)
{
	(void)minirt;
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
