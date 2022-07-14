/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 00:21:57 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/15 02:24:28 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// # include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include "utils.h"
# include "vec3.h"
# include "color.h"
# include "camera.h"

enum e_window {
	WIN_RATIO = 16 / 9,
	WIN_W = 400,
	WIN_H = WIN_W / WIN_RATIO,
	SAMPLES_PER_PIXEL = 100
};

typedef struct s_loop_var {
	int		i;
	int		j;
	int		s;
	double	u;
	double	v;
}				t_loop_var;

typedef struct s_data {
	void	*img;
	char	*buff;
	int		bpp;
	int		bpl;
	int		endian;
}				t_data;

typedef struct s_mlx {
	void		*mlx_ptr;
	void		*win_ptr;
	t_data		data;
}				t_mlx;

#endif