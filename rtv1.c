/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/03/05 15:55:52 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	help(void)
{
	ft_printf("Usage: ./RTv1 filename\n\nIdentify scene/objects/light:\
		\nSCENE:\t\t\tOBJECTS:\t\tLIGHT:\
		\n|camera position|\t|name\t\t|\t|type\t  |\
		\n|camera rotation|\t|start\t\t|\t|intensity|\n|canvas\t\t|\t|end\
		|\t|direction|\n|reflection deep|\t|radius or angle|\
		\n\t\t\t|color|\n\t\t\t|specular|\n\t\t\t|reflection|\
		\n\nObjects name:\nsphere - 1	cylinder - 2	cone - 3	plane - 4\
		\nLight type:\npoint - 1	direction - 2	ambition - 3\
		\n\nscene\t{{0,0,0},{0,0,0},{0,0,0},0}\
		\nobject\t{0,{0,0,0},{0,0,0},0,0,0,0.0}\nlight\t{0,0.0,{0,0,0}}\n");
	return (-1);
}

int			main(int ac, char **av)
{
	t_sdl	data;

	ac != 2 ? exit(help()) : 0;
	parse_param(av[1], &data);
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	data.win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, data.scene.canvas.x, data.scene.canvas.y, 0);
	!data.win ? exit(ft_printf("Window error: %s\n", SDL_GetError())) : 0;
	data.surface = SDL_GetWindowSurface(data.win);
	!data.surface ? exit(ft_printf("Surface error: %s\n", SDL_GetError())) : 0;
	host_fract("./kernel/rtv1.cl", "draw_scene", &data);
	while (1)
	{
		ft_bzero(data.surface->pixels, data.surface->w * data.surface->h * 4);
		kernel_param(&data);
		fps(&data);
		while (SDL_PollEvent(&data.event))
			!event(&data) ? exit(0) : 0;
		SDL_UpdateWindowSurface(data.win);
	}
	return (0);
}
