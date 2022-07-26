/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:49:40 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/26 17:58:56 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*readfile(char *str, int fd)
{
	char	buf[BUFSIZE + 1];
	char	*ptr;
	int		ret;

	ret = read(fd, buf, BUFSIZE);
	while (ret > 0)
	{
		ptr = str;
		buf[ret] = '\0';
		str = ft_strjoin(str, buf);
		if (!str)
			return (NULL);
		free(ptr);
		ret = read(fd, buf, BUFSIZE);
	}
	return (str);
}

t_cam	*get_cam_node(int idx, t_p3 o, t_vec3 nv, int fov)
{
	t_cam	*cam;

	cam = ft_malloc(sizeof(t_cam));
	cam->idx = idx;
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
	new = get_cam_node(scene->cam_nb++, parse_vec3(str),
			normalize(parse_vec3(str)), stoi(str));
	ptr = scene->cam;
	if (!ptr)
		scene->cam = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void	parse_res(t_minirt *rt, char **str)
{
	if (rt->win_w != -1 || rt->win_h != -1)
		put_error("resolution declared multiple times\n");
	next(str);
	rt->win_w = stoi(str);
	rt->win_h = stoi(str);
	if (rt->win_w < 1 || rt->win_w > INFINITY
		|| rt->win_h < 1 || rt->win_h > INFINITY)
		put_error("resolution setting is out of range");
}

void	parse_elems(t_minirt *rt, char *str)
{
	if (*str == '#')
		return ;
	if (*str == 'R' && *(str++))
		parse_res(rt, &str);
	else if (*str == 'A' && *(str++))
		parse_ambient_light(&rt->scene, &str);
	else if (*str == 'C' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_camera(&rt->scene, &str);
	else if (*str == 'L' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_light(&rt->scene, &str);
	else if (*str == 's' && *(str + 1) == 'p' && *(str++) && *(str++))
		parse_sphere(&rt->scene, &str);
	else if (*str == 'p' && *(str + 1) == 'l' && *(str++) && *(str++))
		parse_plane(&rt->scene, &str);
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
		parse_elems(rt, str);
		free(str);
	}
	free(str);
	set_cam(&rt->scene, rt->scene.cam);
}
