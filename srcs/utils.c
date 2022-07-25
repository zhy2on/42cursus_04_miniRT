/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:31:14 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 17:43:06 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_error(char *str)
{
	write(2, "error: ", 7);
	write(2, str, ft_strlen(str));
	exit(1);
}

void	*ft_malloc(unsigned int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		put_error("malloc failed\n");
	return (ptr);
}
