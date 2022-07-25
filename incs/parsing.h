/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:51:19 by junyopar          #+#    #+#             */
/*   Updated: 2022/07/25 14:21:21 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"
# include "vec3.h"

/*
** parsing_C
*/
char	*readfile(char *str, int fd);
void	parse_camera(t_minirt *minirt,t_data *data, char **str);
void	parse_elems(t_minirt *minirt, t_data *data, char **strptr);
void	start_parse(t_minirt *minirt, t_data *data, char *str);
void	parse_file(t_minirt *minirt, t_data *data, char **av);

#endif