/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:58:17 by sergee            #+#    #+#             */
/*   Updated: 2018/03/05 15:51:43 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	close_sdl(t_sdl *data)
{
	SDL_DestroyWindow(data->win);
	SDL_Quit();
	return (0);
}

void		fps(t_sdl *data)
{
	static t_ui	prev;
	static t_ui	fps;
	TTF_Font	*ttf;
	char		*fps_str;
	SDL_Surface	*message;

	fps = 1000 / (SDL_GetTicks() - prev);
	prev = SDL_GetTicks();
	fps_str = ft_itoa(fps);
	ttf = TTF_OpenFont("ARIAL.TTF", 22);
	message = TTF_RenderText_Solid(ttf, fps_str,
		(SDL_Color){255, 255, 255, 255});
	SDL_BlitSurface(message, NULL, data->surface, NULL);
	TTF_CloseFont(ttf);
	SDL_FreeSurface(message);
	ft_memdel((void**)&fps_str);
}

static void	event_move(t_sdl *data)
{
	if (data->event.key.keysym.sym == SDLK_a)
	{
		data->scene.o.z += 5 * sin(data->scene.cam_rot.y * M_PI / 180);
		data->scene.o.x -= 5 * cos(data->scene.cam_rot.y * M_PI / 180);
	}
	else if (data->event.key.keysym.sym == SDLK_d)
	{
		data->scene.o.z -= 5 * sin(data->scene.cam_rot.y * M_PI / 180);
		data->scene.o.x += 5 * cos(data->scene.cam_rot.y * M_PI / 180);
	}
	else if (data->event.key.keysym.sym == SDLK_w)
	{
		data->scene.o.z += 5 * cos(data->scene.cam_rot.y * M_PI / 180);
		data->scene.o.x += 5 * sin(data->scene.cam_rot.y * M_PI / 180);
	}
	else if (data->event.key.keysym.sym == SDLK_s)
	{
		data->scene.o.z -= 5 * cos(data->scene.cam_rot.y * M_PI / 180);
		data->scene.o.x -= 5 * sin(data->scene.cam_rot.y * M_PI / 180);
	}
}

int			event(t_sdl *data)
{
	if (data->event.type == SDL_KEYDOWN)
	{
		if (data->event.key.keysym.sym == SDLK_UP)
			data->scene.cam_rot.x += 5;
		else if (data->event.key.keysym.sym == SDLK_DOWN)
			data->scene.cam_rot.x -= 5;
		else if (data->event.key.keysym.sym == SDLK_LEFT)
			data->scene.cam_rot.y -= 5;
		else if (data->event.key.keysym.sym == SDLK_RIGHT)
			data->scene.cam_rot.y += 5;
		else if (data->event.key.keysym.sym == SDLK_ESCAPE)
			return (close_sdl(data));
		else
			event_move(data);
	}
	else if (data->event.type == SDL_QUIT)
		return (close_sdl(data));
	return (1);
}
