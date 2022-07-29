/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:50:03 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/30 04:28:42 by jihoh            ###   ########.fr       */
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

# define BUFSIZE 32
# define EPSILON 0.00001
# define ALBEDO		1000

enum e_key
{
	ON_KEYDOWN = 2,
	DESTROYNOTIFY = 17,
	KEY_ESC = 53,
	KEY_SPACE = 49
} ;

typedef struct s_img {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		size;
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

typedef struct s_hit
{
	double		time;
	t_p3		point;
	t_vec3		nv;
	int			clr;
}				t_hit;

typedef struct s_ray
{
	t_p3	o;
	t_vec3	dir;
	t_hit	hit;
}			t_ray;

typedef struct s_light
{
	t_p3			o;
	double			br;
	int				clr;
	struct s_light	*next;
}				t_light;

typedef struct s_figures
{
	int					type;
	union u_figures		fig;
	int					clr;
	int					specular;
	double				refl_idx;
	double				refr_idx;
	int					texture;
	t_vec3				nv;
	double				wavelength;
	struct s_figures	*next;
}				t_figures;

typedef struct s_scene
{
	int			xres;
	int			yres;
	int			cam_nb;
	t_cam		*cam;
	t_figures	*figures;
	t_light		*light;
	double		al_br;
	int			al_clr;
	int			bgr;
}				t_scene;

typedef struct s_minirt {
	int			save;
	void		*mlx;
	void		*win;
	t_scene		scene;
}				t_minirt;

/*
** parsing_sphere
*/
void		parse_sphere(t_scene *scene, char **str);
void		parse_plane(t_scene *scene, char **str);

/*
** parsing_utils **
*/
void		next(char **str);
double		stof(char **str);
void		comma(char **str);
int			stoi(char **str);
int			parse_color(char **str);
t_vec3		parse_vec3(char **str);
void		add_figures_back(t_scene *scene, t_figures *new);

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
void		set_cam(t_scene *scene, t_cam *cam);

/*
** render **
*/
void		render_scene(t_minirt *rt, t_cam *cam);

/*
** hit **
*/
int			hit_pl(t_ray *ray, t_figures *elem);
int			hit_sp(t_ray *ray, t_figures *elem);
t_vec3		get_hit_point(t_ray ray);

#endif