/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:21:33 by junyopar          #+#    #+#             */
/*   Updated: 2022/08/11 00:39:16 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_H
# define FIGURES_H

# include "vec3.h"

enum e_type
{
	PL,
	SP,
	CY
} ;

typedef struct s_sphere
{
	t_p3	c;
	double	r;
}				t_sphere;

typedef struct s_plane
{
	t_p3	p;
	t_vec3	nv;
}				t_plane;

typedef struct s_cylinder
{
	t_p3	c;
	t_vec3	nv;
	double	r;
	double	height;
}				t_cylinder;

union			u_figures
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
};

#endif