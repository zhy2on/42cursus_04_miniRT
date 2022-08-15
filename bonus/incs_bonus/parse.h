/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:52:09 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/12 03:23:12 by jihoh            ###   ########.fr       */
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
void		parse_resolution(t_scene *scene, char **pstr, char *error_line);
void		parse_scene(t_scene *scene, char *str, void *mlx);
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

/*
** parse_texture.c **
*/
void		set_xpm_to_mlx(t_xpm_img *xpm_img, char *xpm_file, void *mlx);
t_texture	*get_texture_node(\
						char *id, char *img_file, char *bmp_file, void *mlx);
char		*texture_element(char **pstr);
t_texture	*search_texture(t_texture *texture, char *id);
void		parse_texture(t_scene *scene, char **pstr, void *mlx, \
													char *error_line);

#endif