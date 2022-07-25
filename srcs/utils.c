/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:31:14 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 16:22:04 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	put_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

void	*ft_malloc(unsigned int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		exit(put_error("error: malloc failed\n"));
	return (ptr);
}

