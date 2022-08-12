/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:10:40 by junyopar          #+#    #+#             */
/*   Updated: 2022/08/12 19:11:26 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_hook(int button, int x, int y, t_frctl *frctl)
{
	t_cmplx	cmplx;
	t_point	before;
	t_point	after;
	double	zoom;

	if (y < 0)
		return (0);
	zoom = 1.1f;
	before.x = x;
	before.y = WIN_H - y - 1;
	screen_to_world(&before, &cmplx, frctl);
	if (button == SCROLL_UP)
		frctl->zoom *= 1.0 / zoom;
	else if (button == SCROLL_DOWN)
		frctl->zoom *= zoom;
	else
		return (0);
	world_to_screen(&cmplx, &after, frctl);
	frctl->offx -= before.x - after.x;
	frctl->offy -= before.y - after.y;
	draw_fractol(frctl, &frctl->data);
	return (0);
}