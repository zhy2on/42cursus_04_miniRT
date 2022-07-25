/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:31:14 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 15:49:13 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	put_error(char *str)
{
	write(2, "error: ", 7);
	write(2, str, ft_strlen(str));
	return (1);
}

void	*ft_malloc(unsigned int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		exit(put_error("malloc failed\n"));
	return (ptr);
}
