/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:49:55 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 15:44:35 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	main(int ac, char **av)
{
	t_scene	scene;
	t_light	*light;

	(void)ac;
	init_scene(&scene);
	parse_file(&scene, av);
	printf("%f %d\n", scene.ambient_light, scene.al_color);
	light = scene.l;
	while (light)
	{
		printf("%f %f %f %f %d\n", light->o.e[0], light->o.e[1], light->o.e[2], light->br, light->color);
		light = light->next;
	}
	return (0);
}
