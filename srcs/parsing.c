/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:49:40 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/23 16:08:56 by jihoh            ###   ########.fr       */
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

void	parse_camera(t_minirt *minirt, char **str)
{
	t_cam *elem;
}

void	parse_elems(t_minirt *minirt, char **str)
{
	if (*str == 'C' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_camera(&str);
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
			parse_elems(mlx, data, lst, &str);
		str++;
	}
}

void	parse_file(char **av)
{
	int		fd;
	char	*str;

	fd = open(av[1], O_RDONLY);
	if (fd == -1 || av[1])
		exit(put_error("error: fail to open file\n"));
	str = readfile(str, fd);
	start_parse(str);
}
