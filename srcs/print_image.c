/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 22:56:17 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/05 22:56:57 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

void print_image(t_data *data)
{
	SDL_Window *window;
	SDL_Renderer *ren;
	SDL_Event	event;
	int x;
	int y;

	x = 0;
	window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return ;
	window = SDL_CreateWindow("WOLFCRAFT", SDL_WINDOWPOS_CENTERED, \
			SDL_WINDOWPOS_CENTERED, data->width_file, data->height_file, 0);
	ren = SDL_CreateRenderer(window, -1, 0);
	if (!window || !ren)
		return ;
	y = 0;
	while (data->height_file > y)
	{
		x = 0;
		while (data->width_file > x)
		{
			SDL_SetRenderDrawColor(ren, data->pixel[y][x].r, data->pixel[y][x].v, data->pixel[y][x].b, 255);
			SDL_RenderDrawPoint(ren, x, y);
			x++;
		}
		y++;
	}
	SDL_RenderPresent(ren);
	while (SDL_WaitEvent(&event))
	{
		 if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
		 {
			 SDL_DestroyRenderer(ren);
			 SDL_DestroyWindow(window);
			 SDL_Quit();
		 }
	}
}
