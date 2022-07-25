/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:49:40 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 20:25:43 by jihoh            ###   ########.fr       */
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

void	parse_camera(t_minirt *minirt, char **str)
{
	t_cam	*new;
	t_cam	*ptr;

	next(str);
	new = get_cam_node(minirt->scene.cam_nb++, parse_vec3(str),
			normalize(parse_vec3(str)), stoi(str));
	ptr = minirt->cam;
	if (!ptr)
		minirt->cam = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void	parse_elems(t_minirt *minirt, char **strptr)
{
	char	*str;

	str = *strptr;
	if (*str == 'C' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_camera(minirt, &str);
	else if (*str == 'A' && *(str++))
		parse_ambient_light(&minirt->scene, &str);
	else if (*str == 'L' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_light(&minirt->scene, &str);
	else if (*str == 's' && *(str + 1) == 'p' && *(str++) && *(str++))
		parse_sphere(minirt, &str);
	// else if (*str == 'p' && *(str + 1) == 'l' && *(str++) && *(str++))
	// 	parse_plane(minirt, &str);
	*strptr = str;
}

void	start_parse(t_minirt *minirt, char *str)
{
	while (*str)
	{
		if (*str == '#')
		{
			while (*str && *str != '\n')
				str++;
		}
		else
			parse_elems(minirt, &str);
		str++;
	}
}

void	parse_file(t_minirt *minirt, char **av)
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
	str = (char *)ft_malloc(sizeof(char) * (BUFSIZE + 1));
	str = readfile(str, fd);
	start_parse(minirt, str);
}
