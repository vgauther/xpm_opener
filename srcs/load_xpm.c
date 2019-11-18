/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:32:07 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/18 16:13:20 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

Uint32	set_pixel_color(int a, int r, int g, int b)
{
	return ((a << 24) + (r << 16) + (g << 8) + (b << 0));
}

SDL_Surface *create_surface_from_data(t_data *data)
{
	SDL_Surface *s;
	Uint32 *tmp;
	int x;
	int y;
	int i;

	i = 0;
	s = SDL_CreateRGBSurface(0, data->width_file, data->height_file, 32, 0, 0, 0, 0);
	tmp = (Uint32 *)s->pixels;
	y = 0;
	while (y != data->height_file)
	{
		x = 0;
		while (x != data->width_file)
		{
			tmp[i] = set_pixel_color(0,
				data->pixel[y][x].r, data->pixel[y][x].v, data->pixel[y][x].b);
			x++;
			i++;
		}
		y++;
	}
	s->pixels = (void *)tmp;
	return (s);
}

SDL_Surface *load_xpm(char *name)
{
	SDL_Surface *s;
	t_data data;

	read_xpm(name, &data);
	s = create_surface_from_data(&data);
	return (s);
}
