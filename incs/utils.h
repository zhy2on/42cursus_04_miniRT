/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:27:12 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 15:33:15 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

/*
** utils **
*/
int		put_error(char *str);
void	*ft_malloc(unsigned int size);

#endif