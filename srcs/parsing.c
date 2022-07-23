/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:49:40 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/23 14:41:39 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	put_error(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
	return (1);
}

void	parse_file(char **av)
{
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1 || av[1])
		exit(put_error("error: fail to open file\n"));
}
