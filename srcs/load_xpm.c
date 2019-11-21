/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:32:07 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/21 13:52:28 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

static void		local_messages(int i)
{
	if (i == 0)
		ft_putstr("\n[✓] XPM FILE READ\n");
	else if (1 == i)
		ft_putstr("[✓] SDL_Surface Created\n");
}

Uint32			xpm_set_pixel_color(int a, int r, int g, int b)
{
	return ((a << 24) + (r << 16) + (g << 8) + (b << 0));
}

SDL_Surface		*create_surface_from_data(t_data *data)
{
	SDL_Surface		*s;
	Uint32			*tmp;
	int				x;
	int				y;
	int				i;

	i = 0;
	s = SDL_CreateRGBSurface(0, data->width_file,
		data->height_file, 32, 0, 0, 0, 0);
	tmp = (Uint32 *)s->pixels;
	y = 0;
	while (y != data->height_file)
	{
		x = 0;
		while (x != data->width_file)
		{
			tmp[i] = xpm_set_pixel_color(0,
				data->pixel[y][x].r, data->pixel[y][x].v, data->pixel[y][x].b);
			x++;
			i++;
		}
		y++;
	}
	s->pixels = (void *)tmp;
	return (s);
}

SDL_Surface		*load_xpm(char *name)
{
	SDL_Surface	*s;
	t_data		data;

	read_xpm(name, &data);
	local_messages(0);
	s = create_surface_from_data(&data);
	local_messages(1);
	return (s);
}
