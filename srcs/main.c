/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 00:02:27 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/05 22:10:35 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"
#include <stdio.h>

void ft_messages(int id, void *data)
{
	t_data *d;

	if (id == 1)
	{
		ft_putstr("Analysis in progress for : ");
		ft_putstr((char *)data);
	}
	else if (id == 2)
	{
		ft_putstr("[✓] File found");
	}
	else if (id == 3)
	{
		ft_putstr("[✓] File openable");
	}
	else if (id == 4)
	{
		d = (t_data *)data;
		ft_putstr("Data Image :\n");
		ft_putstr("  - Height : ");
		ft_putnbr(d->height_file);
		ft_putstr("\n  - Width : ");
		ft_putnbr(d->width_file);
		ft_putstr("\n  - Number of color : ");
		ft_putnbr(d->nb_of_color);
		ft_putstr("\n  - Char per pixels : ");
		ft_putnbr(d->nb_char_pix);
	}
	ft_putstr("\n");
}

void ft_error(int id, void *data)
{
	if (id == 1)
	{
		ft_putstr("error : ");
		ft_putstr("file cannont be opened");
		ft_putstr((char *)data);
	}
	else if (id == 2)
	{
		ft_putstr("Usage : ./xpm_opener [image.xpm]");
	}
	ft_putstr("\n");
}

int is_the_file_a_xpm(void)
{
	return (0);
}

int is_the_file_a_correct_file(char *name_file)
{
	int fd;
	char tmp[2];
	int ret;

	fd = open(name_file, O_RDONLY);
	if (fd < 0)
		return (0);
	ft_messages(2, NULL);
	ret = read(fd, tmp, 2);
	tmp[ret] = 0;
	if (tmp[0] == 0)
		return (0);
	ft_messages(3, NULL);
	close(fd);
	return (1);
}

int is_the_file_ok(t_data *data)
{
	is_the_file_a_correct_file(data->file_name);
	is_the_file_a_xpm();
	return(0);
}

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
	color_char = strdup(tmp[0]);
	while(color_char[i])
	{
		if (i != (data->nb_char_pix + 1))
		{
			if (tmp[0][i] == 'c')
			{
				color_char[i] = '0';
				tmp[0][i] = 'a';
			}
		else
		{
			color_char[i] = '1';
		}
		//ft_putstr(color_char);
		//ft_putstr("\n");
		}
		i++;
	}
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
	ft_putstr("|");

	ft_putstr(tmp2[1]);
	ft_putstr("|");

	if (tmp3[0][0] == '#')
	{
		data->colors[i_color] = hex_to_rgb(tmp3[0]);
	}
	else
	{
		data->colors[i_color] = color_already_known(tmp3[0]);
	}
	i = 0;
	if (!(data->colors[i_color].color_id = malloc(sizeof(char) * (data->nb_char_pix + 1))))
		exit (0);
	while(i != data->nb_char_pix)
	{
		data->colors[i_color].color_id[i] = tmp2[0][i];
		i++;
	}
	data->colors[i_color].color_id[i] = 0;

}

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
			{
				return(data->colors[i].r);
			}
			else if (rvb == 'v')
			{
				return(data->colors[i].v);
			}
			else if (rvb == 'b')
				return(data->colors[i].b);
		}
		i++;
	}
	return (0);
}

void open_and_read_file(t_data *data)
{
	int fd;
	int ret;
	int i;
	int i_for_malloc_pixels;
	int j_for_malloc_pixels;
	int x;
	int token_before_img;
	char *buff;
	char *tmp;
	int i_color;
	int an_other;

	i = 0;
	token_before_img = 0;
	j_for_malloc_pixels = 0;
	i_color = 0;

	fd = open(data->file_name, O_RDONLY);
	if (fd < 0)
		exit(0);
	if (!(data->file_content = ft_strnew(0)))
		exit(0);
	while ((ret = get_next_line(fd, &buff)))
	{
		if (i > 2)
		{
			if (i == 3)
			{
				recup_xpm_setting(data, buff);
				if (!(data->colors = malloc(sizeof(t_color) * data->nb_of_color)))
					exit(0);
				i_for_malloc_pixels = 0;
				if (!(data->pixel = malloc(sizeof(t_pixel *) * data->height_file)))
					exit(0);
				while (i_for_malloc_pixels != data->height_file)
				{
					if (!(data->pixel[i_for_malloc_pixels] = malloc(sizeof(t_pixel) * data->width_file)))
						exit(0);
					i_for_malloc_pixels++;
				}
			}
			if (i > 3 && token_before_img == 1 && buff[0] == '"')
			{
				x = 0;
				an_other = 0;
				while (x != data->width_file)
				{
					data->pixel[j_for_malloc_pixels][x].r = find_color_for_pixel(data, buff, 'r', an_other);
					data->pixel[j_for_malloc_pixels][x].v = find_color_for_pixel(data, buff, 'v', an_other);
					data->pixel[j_for_malloc_pixels][x].b = find_color_for_pixel(data, buff, 'b', an_other);
					an_other = an_other + data->nb_char_pix;
					x++;
				}
				j_for_malloc_pixels++;
				i++;
			}

			if (i > 3 && buff[0] == '/' && token_before_img == 0)
				token_before_img = 1;
			if (i > 3 && token_before_img == 0)
			{
				recup_colors(data, buff, i_color);
				i_color++;
			}
			tmp = ft_strdup(data->file_content);
			free(data->file_content);
			data->file_content = ft_strjoin(tmp, buff);
			free(tmp);
		}
		free(buff);
		i++;
	}
}

void print_image(t_data *data)
{
	SDL_Window *window;                    // Declare a pointer
	SDL_Renderer *ren;
	SDL_Event	event;
	int x;
	int y;

	x = 0;
	window = NULL;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return ;

	ft_putnbr(data->width_file);
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

int main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
	{
		ft_error(2, NULL);
		return (0);
	}
	data.file_name = ft_strdup(av[1]);
	ft_messages(1, (void *)data.file_name);
 	is_the_file_ok(&data);
	open_and_read_file(&data);
	print_image(&data);
	(void)ac;
	(void)av;
	return (0);
}
