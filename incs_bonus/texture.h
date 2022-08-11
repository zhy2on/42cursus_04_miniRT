/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:51:38 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/12 00:26:40 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "struct.h"
# include "vec3.h"
# include <math.h>

/*
** texture_mapping.c **
*/
int		texture_mapping(t_hit *hit);
int		image_mapping(double u, double v, t_xpm_img img_map);

/*
** checker_board.c **
*/
int		complementary_color(int clr);
int		checker_board_pattern_at(double u, double v, t_hit hit);

/*
** uv_mapping.c **
*/
void	uv_mapping_plane(double *u, double *v, t_vec3 uv_axis[2], t_hit hit);
void	uv_mapping_sphere(double *u, double *v, t_vec3 uv_axis[2], t_hit hit);
void	uv_mapping_cylinder(double *u, double *v, t_vec3 uv_axis[2], t_hit hit);
void	uv_mapping_cone(double *u, double *v, t_vec3 uv_axis[2], t_hit hit);

#endif