/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 00:02:27 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/11 16:56:14 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"
#include <stdio.h>

/*
** recupere les donnes de la 3 lignes du fichier XPM
*/

void recup_xpm_setting(t_data *data, char *str)
{
	char **tmp;
	char **tmp2;

	tmp = ft_strsplit(str, '"');
	tmp2 = ft_strsplit(tmp[0], ' ');
	data->height_file = ft_atoi(tmp2[1]);
	data->width_file = ft_atoi(tmp2[0]);
	data->nb_of_color = ft_atoi(tmp2[2]);
	data->nb_char_pix = ft_atoi(tmp2[3]);
	free_tab_char(tmp);
	free_tab_char(tmp2);
	ft_messages(4, (void *)data);
}


char *strdup_until(char *str, int max)
{
	int i;
	char *ret;

	i = 0;
	if (!(ret = malloc(sizeof(char) * (max + 1))))
		exit(0);
	while (i != max && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	if (i != max)
	{
		ft_putstr("error\n");
		exit(0);
	}
	ret[i] = 0;
	return(ret);
}

/*
** alloue une str pour le color_id afin de reperer cette couleur parmis les pixels
*/

void recup_color_id(t_data *data, char *str, int i_color)
{
	int i;

	i = 0;
	if (!(data->colors[i_color].color_id = malloc(sizeof(char) * (data->nb_char_pix + 1))))
		exit(0);
	while(i != data->nb_char_pix)
	{
		data->colors[i_color].color_id[i] = str[i];
		i++;
	}
	data->colors[i_color].color_id[i] = 0;
}

char *create_save_to_protect_c(t_data *data, char *str)
{
	char 	*color_char;
	int		i;

	i = 0;
	color_char = strdup(str);
	while(color_char[i])
	{
		if (i != (data->nb_char_pix + 1))
		{
			if (str[i] == 'c')
			{
				color_char[i] = '0';
				str[i] = 'a';
			}
			else
				color_char[i] = '1';
		}
		i++;
	}
	return(color_char);
}

/*
** cette fonction permet de creer une structure contenan une des couleurs en debut de fichier
*/

void recup_colors(t_data *data, char *str, int i_color)
{
	char **tmp;
	char **tmp2;
	char **tmp3;
	char *color_char;
	int i;

	tmp = ft_strsplit(str, '"');
	i = 0;
	color_char = create_save_to_protect_c(data, tmp[0]);
	tmp2 = ft_strsplit(tmp[0], 'c');
	i = 0;
	while (i != (data->nb_char_pix + 1))
	{
		if (color_char[i] == '0')
			tmp2[0][i] = 'c';
		i++;
	}
	i++;
	while (color_char[i])
	{
		if (color_char[i] == '0')
			tmp2[1][i - data->nb_char_pix + 1] = 'c';
		i++;
	}
	tmp3 = ft_strsplit(tmp2[1], ' ');
	data->colors[i_color] = tmp3[0][0] == '#' ? hex_to_rgb(tmp3[0]) : color_already_known(tmp3[0], data);
	recup_color_id(data, tmp2[0], i_color);
	free_tab_char(tmp);
	free_tab_char(tmp2);
	free_tab_char(tmp3);
	free(color_char);
}

/*
** fonction qui permet de trouver parmis toutes les couleurs du fichier la couleur du pixel
*/

int char_pixel_find(char *color_id, char *target, t_data *data, int x)
{
	int i;

	i = 0;
	while (i != data->nb_char_pix)
	{
		if (color_id[i] != target[x + 1])
			return (1);
		i++;
		x++;
	}
	return (0);
}

/*
** cette fonction permet de recuperer les couleurs pour un pixel donné en fonction de son caractere
*/

int find_color_for_pixel(t_data *data, char *c, char rvb, int x)
{
	int i;

	i = 0;
	while (i < data->nb_of_color)
	{
		if (char_pixel_find(data->colors[i].color_id, c, data, x) == 0)
		{
			if (rvb == 'r')
				return(data->colors[i].r);
			else if (rvb == 'v')
				return(data->colors[i].v);
			else if (rvb == 'b')
				return(data->colors[i].b);
		}
		i++;
	}
	return (0);
}

void xpm_setting(t_data *data, char *buff)
{
	int i;

	recup_xpm_setting(data, buff);
	if (!(data->colors = malloc(sizeof(t_color) * data->nb_of_color)))
		exit(0);
	i = 0;
	if (!(data->pixel = malloc(sizeof(t_pixel *) * data->height_file)))
		exit(0);
	while (i != data->height_file)
	{
		if (!(data->pixel[i] = malloc(sizeof(t_pixel) * data->width_file)))
			exit(0);
		i++;
	}
}

void recup_pixel_color(t_data *data, int j, char *buff)
{
	int an_other;
	int x;

	x = 0;
	an_other = 0;
	while (x != data->width_file)
	{
		data->pixel[j][x].r = find_color_for_pixel(data, buff, 'r', an_other);
		data->pixel[j][x].v = find_color_for_pixel(data, buff, 'v', an_other);
		data->pixel[j][x].b = find_color_for_pixel(data, buff, 'b', an_other);
		an_other = an_other + data->nb_char_pix;
		x++;
	}
}

void open_and_read_file(t_data *data)
{
	int fd;
	int ret;
	int i;
	int j_for_pixels;
	int token_before_img;
	char *buff;
	int i_color;

	i = 0;
	token_before_img = 0;
	j_for_pixels = 0;
	i_color = 0;
	if ((fd = open(data->file_name, O_RDONLY)) < 0)
		exit(0);
	while ((ret = get_next_line(fd, &buff)))
	{
		if (i > 2)
		{
			if (i == 3)
				xpm_setting(data, buff);
			if (i > 3 && token_before_img == 1 && buff[0] == '"')
			{
				recup_pixel_color(data, j_for_pixels, buff);
				j_for_pixels++;
			}
			if (i > 3 && buff[0] == '/' && token_before_img == 0)
				token_before_img = 1;
			if (i > 3 && token_before_img == 0)
			{
				recup_colors(data, buff, i_color);
				i_color++;
			}
		}
		free(buff);
		i++;
	}
}

void recup_all_built_in_color(t_data *data)
{
	if (!(data->ck = malloc(sizeof(t_color_known) * (235))))
		exit(0);
	structure_of_color(data);
}



void read_xpm(char *name, t_data *data)
{
	data->file_name = ft_strdup(name);
	ft_messages(1, (void *)data->file_name);
	recup_all_built_in_color(data);
	ft_messages(12, NULL);
	ft_messages(5, NULL);
 	is_the_file_ok(data);
	ft_messages(6, NULL);
	open_and_read_file(data);
}

/*
** tu dois faire la fonction qui transforme ton data en surface sdl
** il faut set h et w qui sont la hauteur et la largeur en pixels
** set un clip rect avec x et y à 0  et w et h as longueur et largeur en pixels
** locked à 0
** pitch à 512 sans doute pour rgba
*/

Uint32	set_pixel_color(int a, int r, int g, int b)
{
	return ((a << 24) + (r << 16) + (g << 8) + (b << 0));
}

SDL_Surface *create_surface_from_data(t_data *data)
{
	SDL_Surface *s;
	Uint32 *tmp;
	int i;
	int x;
	int y;
	int stop;

	s = SDL_CreateRGBSurface(0, data->width_file, data->height_file, 32, 0, 0, 0, 0);
	i = 0;
	stop = data->height_file * data->width_file;
	if (s == NULL)
		ft_putstr("xxxx\n");
	// s->clip_rect.x = 0;
	// s->clip_rect.y = 0;
	// s->clip_rect.h = data->height_file;
	// s->clip_rect.w = data->width_file;
	// s->h = data->height_file;
	// s->w = data->width_file;
	// if(!(tmp = malloc(sizeof(Uint32) * (stop))))
	// 	exit(0);
	tmp = (Uint32 *)s->pixels;
	y = 0;


	while (y != data->height_file)
	{
		x = 0;
		while (x != data->width_file)
		{
			tmp[i] = set_pixel_color(0, data->pixel[y][x].r, data->pixel[y][x].v, data->pixel[y][x].b);
			printf("%d\n", tmp[i]);
			i++;
			x++;
		}
		y++;
	}
	printf("%d\n", tmp[0]);

	s->pixels = (void *)tmp;
	return (s);
}

SDL_Surface *load_xpm(char *name)
{
	SDL_Surface *s;
	t_data data;

	read_xpm(name, &data);
	ft_putstr("--ok--\n");
	s = create_surface_from_data(&data);


	return (s);
}

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
	win = SDL_CreateWindow("WIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 128, 128, 0);
	ren = SDL_CreateRenderer(win, -1, 1);
	r = init_sdl_rect(0, 0, 0, 0);

	s = load_xpm(av[1]);
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

// int main(int ac, char **av)
// {
// 	SDL_Renderer *ren;
// 	SDL_Window *win;
// 	SDL_Rect r;
// 	SDL_Texture	*mon_image;
// 	SDL_Event	event;
// 	SDL_Surface *image;
//
//
// 	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
// 		return 0;
// 	win = SDL_CreateWindow("WIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 128, 128, 0);
// 	ren = SDL_CreateRenderer(win, -1, 1);
// 	r = init_sdl_rect(0, 0, 0, 0);
// 	if (!(image = SDL_LoadBMP(av[1])))
// 		return (0);
// 	ft_putstr(av[1]);
// 	mon_image = SDL_CreateTextureFromSurface(ren, image);
// 	printf("\n\nlocked: %d\n\n", image->pitch);
//
// 	SDL_QueryTexture(mon_image, NULL, NULL, &r.w, &r.h);
// 	SDL_SetRenderTarget(ren, mon_image);
// 	SDL_RenderCopy(ren, mon_image, NULL, &r);
// 	// SDL_FreeSurface(image);
// 	// SDL_DestroyTexture(mon_image);
// 	SDL_RenderPresent(ren);
// 	while (SDL_WaitEvent(&event))
// 	{
// 		 if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
// 		 {
// 			 SDL_DestroyRenderer(ren);
// 			 SDL_DestroyWindow(win);
// 			 SDL_Quit();
// 		 }
// 	}
// 	(void)ac;
// 	return 0;
// }
