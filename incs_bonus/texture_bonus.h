/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:51:38 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 04:02:58 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_BONUS_H
# define TEXTURE_BONUS_H

# include "struct_bonus.h"
# include "vec3_bonus.h"
# include <math.h>

int	checker_board(t_hit hit);
int	complementary_color(int clr);
int	uv_pattern_at(double u, double v, t_hit hit);

#endif