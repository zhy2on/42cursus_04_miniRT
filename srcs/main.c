/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:49:55 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 14:37:52 by jihoh            ###   ########.fr       */
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

	(void)ac;
	init_scene(&scene);
	parse_file(&scene, av);
	printf("hi\n");
	printf("%f %d\n", scene.ambient_light, scene.al_color);
	return (0);
}
