/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 02:28:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/04 02:54:25 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "vec3.h"
# include "struct.h"

/*
** parse.c **
*/
void		set_cam(t_scene *scene, t_cam *cam);
void		parse_resolution(t_scene *scene, char **str);
void		parse_scene(t_scene *scene, char *str);
void		parse_file(t_minirt *rt, char **av);

/*
** parse_cam.c **
*/
t_cam		*get_cam_node(t_p3 o, t_vec3 nv, int fov);
void		parse_camera(t_scene *scene, char **str);

/*
** parse_utils.c **
*/
void		next(char **str);
void		comma(char **str);
t_vec3		parse_vec3(char **str);
double		stof(char **str);
int			parse_color(char **str);

/*
** parse_light.c **
*/
void		parse_ambient_light(t_scene *scene, char **str);
t_light		*get_light_node(t_p3 o, double br, int clr);
void		parse_light(t_scene *scene, char **str);

/*
** parse_figures.c **
*/
t_figures	*get_figures_node(int type);
void		parse_sphere(t_scene *scene, char **str);
void		parse_plane(t_scene *scene, char **str);
void		parse_cylinder(t_scene *scene, char **str);
void		add_figures_back(t_scene *scene, t_figures *new);

#endif