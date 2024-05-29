/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:11:41 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/29 14:49:13 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"

static int	put_points(t_fdata *d)
{
	int			i;
	t_point		*arr;

	write(1, "put_points\n", 11);
	if (!d->img.ptr)
		create_image(d);
	arr = d->pts.arr;
	i = 0;
	while (i < d->pts.size)
	{
		arr[i].x = (WIDTH/2) + (arr[i].i * d->img.sp);
		arr[i].y = (HEIGHT/2) + (arr[i].j * d->img.sp);
		arr[i].visible = true;
		if (arr[i].x < WIDTH && arr[i].y < HEIGHT)
			put_pixel_img(&d->img, arr[i].x, arr[i].y, arr[i].color);
		else
			arr[i].visible = false;
		i++;
	}
	draw_lines(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img.ptr, d->img.offset,
		d->img.offset);
	return (1);
}

int	refresh_display(t_fdata *d)
{
	//Optimization: instead of creating a black image then putting points,
	//fill all the image that doesn't have a point with black at each put_points
	if (!d->img.ptr)
		return (0);
	if (d->img.old_sp != d->img.sp)
	{
		ft_bzero(d->img.addr, d->img.size * HEIGHT);
		d->img.old_sp = d->img.sp;
		return (put_points(d));
	}
	return (1);
}

void	display(t_fdata *d)
{
	d->mlx = mlx_init();
	if (!d->mlx)
		stop_error("Error at mlx initialization", d);
	config_img(d);
	d->win = mlx_new_window(d->mlx, WIDTH + d->img.offset,
			HEIGHT + d->img.offset, "FdF");
	if (!d->win)
		stop_error("Error at mlx window initialization", d);
	put_points(d);
	mlx_loop_hook(d->mlx, &refresh_display, d);
	mlx_hook(d->win, DESTROY, 0, &handle_close, d);
	mlx_hook(d->win, KEYDOWN, 1L << 0, &handle_key, d);
	mlx_loop(d->mlx);
}
