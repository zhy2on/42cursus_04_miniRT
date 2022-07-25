/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:50:03 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/25 17:27:23 by junyopar         ###   ########.fr       */
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
# include "figures.h"

// # include "parsing.h"

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
// typedef struct s_cam
// {
// 	double	aspect_ratio;
// 	double	vport_h;
// 	double	vport_w;
// 	double	focal_len;
// 	t_p3	origin;
// 	t_vec3	l_l_c;
// 	t_vec3	horizontal;
// 	t_vec3	vertical;
// }				t_cam;*/

typedef struct s_data {
	void	*img;
	char	*buff;
	int		bpp;
	int		bpl;
	int		endian;
	int		cam_num;
}				t_data;

typedef struct s_cam
{
	int				idx;
	t_p3			o;
	t_vec3			nv;
	int				fov;
	t_data			data;
	struct s_cam	*next;
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
	int				xres;
	int				yres;
	int				cam_nb;
	t_light			*l;
	double			ambient_light;
	int				al_color;
	int				bgr;
}				t_scene;

typedef struct s_minirt {
	void		*mlx_ptr;
	void		*win_ptr;
	t_cam		*cam;
	t_scene		scene;
}				t_minirt;
// figures
typedef struct s_figures
{
	int				flag;
	union u_figures	fig;
	int				color;
	int				specular;
	double			refl_idx;
	double			refr_idx;
	int				texture;
	t_p3			normal;
	double			wavelength;
	struct s_figures *next;
}				t_figures;

/*
** parsing_sphere
*/
void		parse_sphere(t_figures **elem, char **str);
void		parse_plane(t_figures **elem, char **str);

/*
** parsing_utils **
*/
void	next(char **str);
double	stof(char **str);
void    comma(char **str);
int	    stoi(char **str);
int	    parse_color(char **str);
t_vec3  parse_vec3(char **str);
void	ft_addnewlst_back(t_figures **alst);

/*
** parsing
*/
char	*readfile(char *str, int fd);
void	parse_file(t_minirt *minirt, t_data *data, t_figures **lst, char **av);
void	start_parse(t_minirt *minirt, t_data *data, t_figures **lst, char *str);
void	parse_elems(t_minirt *minirt, t_data *data, t_figures **lst, char **strptr);

/*
** parsing_light
*/
void	init_scene(t_scene *scene);
void	parse_ambient_light(t_scene *scene, char **str);
void	parse_light(t_scene *scene, char **str);

/*
** utils **
*/
void	put_error(char *str);
void	*ft_malloc(unsigned int size);

#endif