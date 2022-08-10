/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 01:26:17 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 04:06:01 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	set_xpm_to_mlx(t_xpm_img *xpm_img, char *xpm_file, void *mlx)
{
	if (xpm_file && ft_strcmp(xpm_file, "NULL"))
	{
		if (!ft_strncmp((xpm_file + ft_strlen(xpm_file) - 4), ".xpm", 3))
			put_error("texture file format must be .xpm", xpm_file);
		xpm_img->ptr = mlx_xpm_file_to_image(mlx,
				xpm_file, &xpm_img->w, &xpm_img->h);
		xpm_img->addr = mlx_get_data_addr(xpm_img->ptr,
				&xpm_img->bpp, &xpm_img->size, &xpm_img->endian);
		if (!xpm_img->ptr || !xpm_img->addr)
			put_error("fail to handle xpm file", xpm_file);
	}
	else
	{
		xpm_img->ptr = NULL;
		xpm_img->addr = NULL;
	}
}

t_texture	*get_texture_node(char *id, char *img_file,
		char *bmp_file, void *mlx)
{
	t_texture	*texture;

	texture = ft_malloc(sizeof(t_texture));
	texture->id = id;
	set_xpm_to_mlx(&texture->img_map, img_file, mlx);
	set_xpm_to_mlx(&texture->bmp_map, bmp_file, mlx);
	texture->next = NULL;
	return (texture);
}

void	push_texure_node(t_scene *scene, t_texture *new)
{
	if (!scene->texture)
		scene->texture = new;
	else
	{
		new->next = scene->texture;
		scene->texture = new;
	}
}

void	parse_texture(t_scene *scene, char **pstr, void *mlx)
{
	char		*id;
	char		*img_file;
	char		*bmp_file;
	char		*str;
	t_texture	*new;

	next(pstr);
	str = *pstr;
	while (**pstr && **pstr != 9 && **pstr != 32)
		(*pstr)++;
	id = ft_strndup(str, *pstr - str);
	str = *pstr;
	while (**pstr && **pstr != 9 && **pstr != 32)
		(*pstr)++;
	img_file = ft_strndup(str, *pstr - str);
	str = *pstr;
	while (**pstr && **pstr != 9 && **pstr != 32)
		(*pstr)++;
	bmp_file = ft_strndup(str, *pstr - str);
	new = get_texture_node(id, img_file, bmp_file, mlx);
	push_texure_node(scene, new);
	free(img_file);
	free(bmp_file);
}
