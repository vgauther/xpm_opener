/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 22:56:17 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/11 17:57:24 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

void wait_ev(SDL_Renderer *ren, SDL_Window *win)
{
	SDL_Event	event;

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

void print_image(t_data *data)
{
	SDL_Window *window;
	SDL_Renderer *ren;
	int x;
	int y;

	x = 0;
	window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return ;
	ft_messages(-1, NULL);
	window = SDL_CreateWindow("XPM", SDL_WINDOWPOS_CENTERED, \
			SDL_WINDOWPOS_CENTERED, data->width_file, data->height_file, 0);
	ft_messages(-2, NULL);
	ren = SDL_CreateRenderer(window, -1, 0);
	ft_messages(-3, NULL);
	if (!window || !ren)
		return ;
	y = 0;
	ft_messages(-4, NULL);
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
	ft_messages(-5, NULL);
	SDL_RenderPresent(ren);
	ft_messages(-6, NULL);
	wait_ev(ren, win);
}
