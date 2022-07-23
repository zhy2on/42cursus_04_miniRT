/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:50:03 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/23 16:08:40 by jihoh            ###   ########.fr       */
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

# define BUFSIZE 32

enum e_key
{
	ON_KEYDOWN = 2,
	DESTROYNOTIFY = 17,
	KEY_ESC = 53
} ;

/*
** vport_h : viewport_height
** vport_w : viewport_width
** focal_len: focal_length, distance from camera to the viewport
** origin : camera position
** l_l_c : lower_left_corner of viewport
*//*
typedef struct s_cam
{
	double	aspect_ratio;
	double	vport_h;
	double	vport_w;
	double	focal_len;
	t_p3	origin;
	t_vec3	l_l_c;
	t_vec3	horizontal;
	t_vec3	vertical;
}				t_cam;*/

typedef struct s_data {
	void	*img;
	char	*buff;
	int		bpp;
	int		bpl;
	int		endian;
}				t_data;

typedef struct s_cam
{
	int				idx;
	t_p3			o;
	t_vec3			nv;
	int				fov;
	t_data			data;
	struct s_camera	*next;
}				t_cam;

typedef struct s_ray
{
	t_p3	orig;
	t_vec3	dir;
}			t_ray;

typedef struct s_light
{
	t_p3			o;
	double			br;
	int				color;
	struct s_light	*next;
}				t_light;

typedef struct s_scene
{
	int				res_init;
	int				xres;
	int				yres;
	int				cam_nb;
	t_light			*l;
	int				al_init;
	double			ambient_light;
	int				al_color;
	int				bgr;
}				t_scene;

typedef struct s_minirt {
	void		*mlx_ptr;
	void		*win_ptr;
	t_cam		*cam;
}				t_minirt;

/*
** utils **
*/
int		put_error(char *str);
void	*ft_malloc(unsigned int size);

#endif