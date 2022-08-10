/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:52:09 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 03:52:10 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

# include "vec3_bonus.h"
# include "struct_bonus.h"

/*
** parse.c **
*/
void		set_cam(t_scene *scene, t_cam *cam);
void		parse_resolution(t_scene *scene, char **pstr, char *error_line);
void		parse_scene(t_scene *scene, char *str);
void		parse_file(t_minirt *rt, char *av);

/*
** parse_cam.c **
*/
t_cam		*get_cam_node(t_p3 o, t_vec3 nv, int fov);
void		parse_camera(t_scene *scene, char **pstr, char *error_line);

/*
** parse_utils.c **
*/
void		next(char **pstr);
void		comma(char **pstr, char *error_line);
t_vec3		parse_vec3(char **pstr, char *error_line);
double		stof(char **pstr);
int			parse_color(char **pstr, char *error_line);

/*
** parse_light.c **
*/
void		parse_ambient_light(t_scene *scene, char **pstr, char *error_line);
t_light		*get_light_node(t_p3 o, double br, int clr);
void		parse_light(t_scene *scene, char **pstr, char *error_line);

/*
** parse_figures.c **
*/
void		parse_sphere(t_scene *scene, char **pstr, char *error_line);
void		parse_plane(t_scene *scene, char **pstr, char *error_line);
void		parse_cylinder(t_scene *scene, char **pstr, char *error_line);
void		parse_cone(t_scene *scene, char **pstr, char *error_line);

/*
** parse_figures_utils.c **
*/
t_figures	*get_figures_node(int type);
void		check_figures_setting(t_figures elem, char *error_line);
void		push_figures_node(t_scene *scene, t_figures *new);

#endif