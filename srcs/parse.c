/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:49:40 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/02 18:05:44 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam	*get_cam_node(t_p3 o, t_vec3 nv, int fov)
{
	t_cam	*cam;

	cam = ft_malloc(sizeof(t_cam));
	cam->o = o;
	cam->nv = nv;
	cam->fov = fov;
	cam->next = NULL;
	return (cam);
}

void	parse_camera(t_scene *scene, char **str)
{
	t_cam	*new;
	t_cam	*ptr;

	next(str);
	new = get_cam_node(parse_vec3(str),
			normalize(parse_vec3(str)), stof(str));
	ptr = scene->cam;
	if (!ptr)
	{
		scene->first = new;
		scene->cam = new;
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void	parse_resolution(t_scene *scene, char **str)
{
	if (scene->xres != -1 || scene->yres != -1)
		put_error("resolution declared multiple times\n");
	next(str);
	scene->xres = stof(str);
	scene->yres = stof(str);
	if (scene->xres < 1 || scene->xres > INFINITY
		|| scene->yres < 1 || scene->yres > INFINITY)
		put_error("resolution setting is out of range");
}

void	parse_scene(t_scene *scene, char *str)
{
	if (*str == '#')
		return ;
	if (*str == 'R' && *(str++))
		parse_resolution(scene, &str);
	else if (*str == 'A' && *(str++))
		parse_ambient_light(scene, &str);
	else if (*str == 'C' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_camera(scene, &str);
	else if (*str == 'L' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_light(scene, &str);
	else if (*str == 's' && *(str + 1) == 'p' && *(str++) && *(str++))
		parse_sphere(scene, &str);
	else if (*str == 'p' && *(str + 1) == 'l' && *(str++) && *(str++))
		parse_plane(scene, &str);
	else if (*str == 'c' && *(str + 1) == 'y' && *(str++) && *(str++))
		parse_cylinder(scene, &str);
}

void	parse_file(t_minirt *rt, char **av)
{
	int		fd;
	char	*str;
	int		len;

	len = ft_strlen(av[1]);
	if (!av[1] || len < 3 || av[1][len - 1] != 't'
		|| av[1][len - 2] != 'r' || av[1][len - 3] != '.')
		put_error("file format must be .rt\n");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		put_error("fail to open file\n");
	str = NULL;
	while (get_next_line(fd, &str) > 0)
	{
		parse_scene(&rt->scene, str);
		free(str);
	}
	free(str);
	set_cam(&rt->scene, rt->scene.cam);
}
