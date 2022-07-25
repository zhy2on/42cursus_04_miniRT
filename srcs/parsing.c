/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:49:40 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/23 17:40:41 by jihoh            ###   ########.fr       */
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

t_vec3 parse_vec3(char **str)
{
	t_vec3 vec;
	
	vec.e[0] = stof(str);
	comma(str);
	vec.e[1] = stof(str);
	comma(str);
	vec.e[2] = stof(str);
	next(str);
	return (vec);
}

void	parse_camera(t_minirt *minirt,t_data *data, char **str)
{
	t_cam 	*elem;
	t_cam 	*begin;
	int 	prev_idx;

	prev_idx = 0;
	begin = minirt->cam;
	elem = ft_malloc(sizeof(t_cam));
	elem->next = NULL;
	if(minirt->cam)
	{
		while (minirt->cam->next)
			minirt->cam = minirt->cam->next;
		prev_idx = minirt->cam->idx;
		minirt->cam->next = elem;
	}
	else
		minirt->cam = elem;
	while(**str == 32 || **str == 9)
		(*str)++;
	elem->idx = prev_idx + 1;
	data->cam_num = elem->idx;
	elem->o = parse_vec3(str);
	elem->nv = normalize(parse_vec3(str));
	elem->fov = stoi(str);
	in_range(elem->fov, 0, 180, "camera");
	if (minirt->cam == begin)
		minirt->cam = begin;
	else if (minirt->cam != begin)
		minirt->cam = elem;
}

void	parse_elems(t_minirt *minirt, t_data *data, char **strptr)
{
	char *str;
	str = *strptr;

	if (*str == 'C' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_camera(minirt, data, &str);
}

void	start_parse(t_minirt *minirt, t_data *data, char *str)
{
	while (*str)
	{
		if (*str == '#')
		{
			while (*str && *str != '\n')
				str++;
		}
		else
			parse_elems(minirt, data, &str);
		str++;
	}
}

void	parse_file(t_minirt *minirt, t_data *data, char **av)
{
	int		fd;
	char	*str;

	fd = open(av[1], O_RDONLY);
	if (fd == -1 || av[1])
		exit(put_error("error: fail to open file\n"));
	str = readfile(str, fd);
	start_parse(minirt, data, str);
}
