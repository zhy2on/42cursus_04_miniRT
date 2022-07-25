/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:27:12 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 15:38:14 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>
#include "minirt.h"
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
void    comma(char **str);
int	    stoi(char **str);
int	    parse_color(char **str);
t_vec3  parse_vec3(char **str);
void		ft_addnewlst_back(t_figures **alst);

#endif