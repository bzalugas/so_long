/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:01:15 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/14 14:58:39 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	handle_close(t_fdata *data)
{
	end_fdf(data, 0);
	exit(0);
}

int	handle_mouse(int but, int x, int y, t_fdata *d)
{
	(void)x;
	(void)y;
	if (but == MS_WHEEL_UP)
		return (zoom_in(d));
	else if (but == MS_WHEEL_DN)
		return (zoom_out(d));
	return (1);
}

static int	handle_key2(int key, t_fdata *d)
{
	if (key == KEY_C)
		return (toggle_colors(d));
	else if (key == KEY_J || key == KEY_K)
		return (change_elevation(d, key));
	else if (key == KEY_R)
		return (reset(d));
	else if (key == KEY_L)
		return (toggle_lines(d));
	else if (key == KEY_P)
		return (toggle_projection(d));
	else
		return (1);
}

int	handle_key(int key, t_fdata *data)
{
	if (key == ESC)
		return (handle_close(data));
	else if (key == KEY_I)
		return (zoom_in(data));
	else if (key == KEY_O)
		return (zoom_out(data));
	else if (key == KEY_SP)
	{
		data->img.rot_mode = -data->img.rot_mode;
		dynamic_hud(data, false);
	}
	else if (data->img.rot_mode == 1 && (key == KEY_Q || key == KEY_E
			|| key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D))
		return (rotate(data, key));
	else if (data->img.rot_mode == -1 && (key == KEY_W || key == KEY_S
			|| key == KEY_A || key == KEY_D))
		return (translate(data, key));
	else
		return (handle_key2(key, data));
	return (1);
}
