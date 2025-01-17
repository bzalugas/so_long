/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:49:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/14 15:12:29 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"
#include "../include/libft.h"

void	normalize_coords(t_fdata *d, t_point *origin)
{
	size_t	i;
	t_point	mid;

	if (!origin)
		mid = d->pts.arr[(d->pts.r / 2) * d->pts.c + (d->pts.c / 2)];
	else
		mid = *origin;
	i = 0;
	while (i < d->pts.size)
	{
		d->pts.arr[i].i = d->pts.arr[i].i - mid.i;
		d->pts.arr[i].j = d->pts.arr[i].j - mid.j;
		i++;
	}
}

void	create_image(t_fdata *d)
{
	d->img.ptr = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->img.ptr)
		stop_error("Error while creating image", d);
	d->img.addr = mlx_get_data_addr(d->img.ptr, &d->img.bpp, &d->img.size,
			&d->img.end);
}

void	config_img(t_fdata *d)
{
	int	max;

	d->img.offset[0] = DEFAULT_OFFSETX;
	d->img.offset[1] = DEFAULT_OFFSETY;
	d->img.center[0] = WIDTH / 2;
	d->img.center[1] = HEIGHT / 2;
	max = ft_max(d->pts.r, d->pts.c);
	d->img.sp = ft_max((WIDTH / 2) / max, (HEIGHT / 2) / max);
	if (d->img.sp < DEFAULT_SPACE)
		d->img.sp = DEFAULT_SPACE;
	d->img.elev = 1.0;
	d->img.ptslines = ft_cylloc(HEIGHT * WIDTH, sizeof(t_ptline), &d->trash);
	if (!d->img.ptslines)
		stop_error("ptslines allocation error", d);
	d->img.rx = DEFAULT_DEG_X;
	d->img.ry = 0;
	d->img.rz = DEFAULT_DEG_Z;
	d->img.rot_mode = 1;
	rotate_img(d, AXIS_Z, true);
	rotate_img(d, AXIS_X, false);
	d->img.tog_lines = 1;
	d->img.projection = 1;
}
