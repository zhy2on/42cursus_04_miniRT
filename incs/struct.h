/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 02:33:56 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/07 16:47:59 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "vec3.h"
# include "figures.h"

typedef struct s_img {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		size;
	int		endian;
}				t_img;

typedef struct s_cam
{
	t_p3			o;
	t_vec3			nv;
	int				fov;
	t_vec3			hor;
	t_vec3			ver;
	t_vec3			llc;
	t_img			img;
	struct s_cam	*next;
}				t_cam;

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
	double				wavelength;
	struct s_figures	*next;
}				t_figures;

typedef struct s_hit
{
	double		time;
	t_p3		point;
	t_vec3		nv;
	t_figures	elem;
}				t_hit;

typedef struct s_ray
{
	t_p3	o;
	t_vec3	dir;
	t_hit	hit;
}			t_ray;

typedef struct s_scene
{
	int			xres;
	int			yres;
	t_cam		*first;
	t_cam		*cam;
	t_figures	*figures;
	t_light		*light;
	double		al_br;
	int			al_clr;
}				t_scene;

typedef struct s_minirt {
	void		*mlx;
	void		*win;
	t_scene		scene;
}				t_minirt;

#endif