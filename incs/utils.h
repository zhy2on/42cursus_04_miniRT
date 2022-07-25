/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:27:12 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/23 17:28:42 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
** utils **
*/
int		put_error(char *str);
void	*ft_malloc(unsigned int size);

/*
** parsing_utils **
*/
void	next(char **str);
double	stof(char **str);

#endif