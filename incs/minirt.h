/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:50:03 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/10 18:20:54 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <mlx.h>
# include <fcntl.h>
# include "libft.h"
# include "vec3.h"
# include "struct.h"
# include "figures.h"
# include "parse.h"
# include "raytrace.h"

# define BUFSIZE 32
# define EPSILON 0.00001

# define WIN_W	800
# define WIN_H	800

# define RED "\033[31m"
# define YELLOW "\033[33m"

enum e_window
{
	MAX_W = 800,
	MIN_W = 480
} ;

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
void		put_error(char *str, char *stop);
void		*ft_malloc(unsigned int size);
double		clamp(double x, double min, double max);
void		set_uv_axis(t_vec3 w, t_vec3 *u, t_vec3	*v);

/*
** render.c **
*/
t_ray		create_ray(t_cam *cam, double x, double y);
void		set_pixel_color(t_img *img, int x, int y, int colour);
void		render_scene(t_minirt *rt, t_cam *cam);

#endif