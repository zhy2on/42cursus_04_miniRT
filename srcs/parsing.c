/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:49:40 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 14:49:08 by jihoh            ###   ########.fr       */
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

void	parse_camera(t_scene *scene, char **str)
{
	(void)scene;
	(void)str;
}

void	parse_elems(t_scene *scene, char **strptr)
{
	char	*str;

	str = *strptr;
	if (*str == 'C' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_camera(scene, &str);
	else if (*str == 'A' && *(str++))
		parse_ambient_light(scene, &str);
	*strptr = str;
}

void	start_parse(t_scene *scene, char *str)
{
	while (*str)
	{
		if (*str == '#')
		{
			while (*str && *str != '\n')
				str++;
		}
		else
			parse_elems(scene, &str);
		str++;
	}
}

void	parse_file(t_scene *scene, char **av)
{
	int		fd;
	char	*str;
	int		len;

	len = ft_strlen(av[1]);
	if (len < 3 || av[1][len - 1] != 't'
		|| av[1][len - 2] != 'r' || av[1][len - 3] != '.')
		exit(put_error("file format must be .rt\n"));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(put_error("fail to open file\n"));
	str = (char *)ft_malloc(sizeof(char) * (BUFSIZE + 1));
	str = readfile(str, fd);
	start_parse(scene, str);
}
