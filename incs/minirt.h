/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:50:03 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/04 19:30:59 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <mlx.h>
# include <fcntl.h>
# include "vec3.h"
# include "libft.h"
# include "struct.h"
# include "figures.h"
# include "parse.h"
# include "raytrace.h"

# define BUFSIZE 32
# define EPSILON 0.00001
# define ALBEDO	150

enum e_key
{
	ON_KEYDOWN = 2,
	DESTROYNOTIFY = 17,
	KEY_ESC = 53,
	KEY_SPACE = 49
} ;

/*
** utils.c **
*/
void		put_error(char *str);
void		*ft_malloc(unsigned int size);
double		time_clamp(double x);
t_p3		get_hit_point(t_ray ray);
void		solve_quadratic(double a, double b, double c, double root[2]);

/*
** render.c **
*/
t_ray		create_ray(t_cam *cam, double x, double y);
void		set_pixel_color(t_img *img, int x, int y, int colour);
void		render_scene(t_minirt *rt, t_cam *cam);

/*
** color.c **
*/
// int			ccomp(t_light *light, t_hit hit);
int			ccomp(t_light *light, t_ray ray, t_minirt *rt);
int			cadd(int c1, int c2);
int			cprod(int c1, int c2);
int			cscale(int color, double d);
int			check_rgb(int n);
t_vec3		reflect_ray(t_p3 ray, t_p3 normal);
#endif