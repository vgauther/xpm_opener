/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 00:02:27 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/19 11:13:06 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

SDL_Rect init_sdl_rect(int x, int y, int i, int j)
{
	SDL_Rect r;

	r.x = x;
	r.y = y;
	r.h = j;
	r.w = i;
	return (r);
}

void print_surface(SDL_Renderer *ren, SDL_Surface *image, SDL_Rect r)
{
	SDL_Texture	*mon_image;

	mon_image = SDL_CreateTextureFromSurface(ren, image);
	SDL_QueryTexture(mon_image, NULL, NULL, &r.w, &r.h);
	SDL_SetRenderTarget(ren, mon_image);
	SDL_RenderCopy(ren, mon_image, NULL, &r);
	SDL_FreeSurface(image);
	SDL_DestroyTexture(mon_image);
}

int main(int ac, char **av)
{
	SDL_Rect r;
	SDL_Surface *s;
	SDL_Renderer *ren;
	SDL_Event	event;
	SDL_Window *win;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return 0;
	s = load_xpm(av[1]);
	win = SDL_CreateWindow("WIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, s->w, s->h, 0);
	ren = SDL_CreateRenderer(win, -1, 1);
	r = init_sdl_rect(0, 0, 0, 0);
	print_surface(ren, s, r);
	SDL_RenderPresent(ren);
	while (SDL_WaitEvent(&event))
	{
		 if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
		 {
			 SDL_DestroyRenderer(ren);
			 SDL_DestroyWindow(win);
			 SDL_Quit();
		 }
	}
	return (0);
	(void)ac;
	(void)av;
}
