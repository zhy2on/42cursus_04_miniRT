/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:50:03 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/26 16:14:38 by jihoh            ###   ########.fr       */
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

typedef struct s_img {
	void	*ptr;
	char	*buff;
	int		bpp;
	int		bpl;
	int		endian;
}				t_img;

typedef struct s_cam
{
	int				idx;
	t_p3			o;
	t_vec3			nv;
	int				fov;
	t_vec3			hor;
	t_vec3			ver;
	t_vec3			llc;
	t_img			img;
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

typedef struct s_figures
{
	int					flag;
	union u_figures		fig;
	int					color;
	int					specular;
	double				refl_idx;
	double				refr_idx;
	int					texture;
	t_p3				normal;
	double				wavelength;
	struct s_figures	*next;
}				t_figures;

typedef struct s_minirt {
	void		*mlx;
	void		*win;
	int			win_w;
	int			win_h;
	t_cam		*cam;
	t_figures	*figures;
	t_scene		scene;
}				t_minirt;

/*
** parsing_sphere
*/
void		parse_sphere(t_minirt *rt, char **str);
void		parse_plane(t_minirt *rt, char **str);

/*
** parsing_utils **
*/
void		next(char **str);
double		stof(char **str);
void		comma(char **str);
int			stoi(char **str);
int			parse_color(char **str);
t_vec3		parse_vec3(char **str);
void		add_figures_back(t_minirt *rt, t_figures *new);

/*
** parsing
*/
char		*readfile(char *str, int fd);
void		parse_file(t_minirt *rt, char **av);
void		parse_elems(t_minirt *rt, char *str);

/*
** parsing_light
*/
void		init_scene(t_scene *scene);
void		parse_ambient_light(t_scene *scene, char **str);
void		parse_light(t_scene *scene, char **str);

/*
** utils **
*/
void		put_error(char *str);
void		*ft_malloc(unsigned int size);

/*
** cam **
*/
void		cam_setting(t_scene *scene, t_cam *cam);

#endif