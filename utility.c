/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:58:17 by sergee            #+#    #+#             */
/*   Updated: 2018/03/02 12:26:29 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	fps(t_sdl *data)
{
	static t_ui	prev;
	static t_ui	fps;
	char		*fps_str;
	SDL_Surface	*message;

	fps = 1000 / (SDL_GetTicks() - prev);
	prev = SDL_GetTicks();
	fps_str = ft_itoa(fps);
	message = TTF_RenderText_Solid(TTF_OpenFont("ARIAL.TTF", 22),
		fps_str, (SDL_Color){255, 255, 255, 255});
	SDL_BlitSurface(message, NULL, data->surface, NULL);
	ft_memdel((void**)&fps_str);
}
