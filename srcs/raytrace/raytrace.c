/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:47:08 by jihoh             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/04 17:22:14 by junyopar         ###   ########.fr       */
=======
/*   Updated: 2022/08/04 05:12:42 by jihoh            ###   ########.fr       */
>>>>>>> 91064784e75ade4db7b06b87f090183ecaf95dcb
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect(t_minirt *rt, t_ray *ray)
{
	int			ret;
	t_figures	*elem;

	ray->hit.time = INFINITY;
	ret = 0;
	elem = rt->scene.figures;
	while (elem)
	{
		if (elem->type == PL)
			ret |= hit_plane(ray, *elem);
		else if (elem->type == SP)
			ret |= hit_sphere(ray, *elem);
		else if (elem->type == CY)
			ret |= hit_cylinder(ray, *elem);
		elem = elem->next;
	}
	return (ret);
}

int	in_shadow(t_minirt *rt, t_hit hit, t_light *light)
{
	t_ray	shadow;
	double	inter;

	shadow.o = hit.point;
	shadow.dir = normalize(vsub(light->o, hit.point));
	inter = intersect(rt, &shadow);
	if (distance(hit.point, light->o) <= distance(hit.point, shadow.hit.point))
		return (0);
	return (inter);
}

t_p3		refract_ray(t_p3 d, t_p3 normal, t_figures *lst)
{
	double	cosi;
	double	etai;
	double	etat;
	double	eta;
	double	k;

	cosi = dot(d, normal);
	etai = 1;
	etat = lst->refr_idx;
	if (lst->fig.sp.inside == 1)
	{
		k = etai;
		etai = etat;
		etat = k;
	}
	eta = etai / etat;
	k = 1 - eta * eta * (1 - cosi * cosi);
	return (k < 0 ? reflect_ray(vscale(d, -1), normal): vadd(vscale(d, eta), vscale(normal, eta * cosi - sqrt(k))));
}

int	raytrace(t_minirt *rt, t_ray *ray)
{
	int		al_clr;
	int		clr;
	int		vis;
	t_light	*light;

	if (!intersect(rt, ray))
		return (0);
	al_clr = cscale(rt->scene.al_clr, rt->scene.al_br);
	clr = cprod(ray->hit.elem.clr, al_clr);
	light = rt->scene.light;
	// refract_ray(ra)
	while (light)
	{
		vis = !in_shadow(rt, ray->hit, light);
		clr = cadd(clr, vis * ccomp(light, *ray, rt));
		light = light->next;
	}
	return (clr);
}
