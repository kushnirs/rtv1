/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:50:28 by sergee            #+#    #+#             */
/*   Updated: 2018/02/23 10:58:50 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		close_window(t_mlx *data)
{
	mlx_destroy_window(data->mlx, data->win);
	return (0);
}

int		key_action(int key, t_mlx *data)
{
	(void)data;
	key == ESC ? exit(0) : 0;
	return (0);
}

int		mouse_action(int button, int x, int y, t_mlx *data)
{
	return (0);
}
