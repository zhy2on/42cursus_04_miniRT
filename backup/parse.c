/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:49:40 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/04 20:06:13 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_cam(t_scene *scene, t_cam *cam)
{
	double	vp[2];
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;

	while (cam)
	{
		vp[0] = 2 * tan(cam->fov / 2);
		vp[1] = vp[0] * (double)scene->yres / scene->xres;
		w = normalize(vscale(cam->nv, -1));
		if (w.y == 1 || w.y == -1)
			u = create_vec3(w.y, 0, 0);
		else
			u = cross(create_vec3(0, 1, 0), w);
		v = cross(w, u);
		cam->hor = vscale(u, vp[0]);
		cam->ver = vscale(v, vp[1]);
		cam->llc = vsub(cam->o, vscale(cam->hor, 0.5));
		cam->llc = vsub(cam->llc, vscale(cam->ver, 0.5));
		cam->llc = vsub(cam->llc, w);
		cam = cam->next;
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
