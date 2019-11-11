/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:39:43 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/11 17:50:22 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

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
	if(!(color_char = ft_strdup(str)))
		return (NULL);
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
	if (!(color_char = create_save_to_protect_c(data, tmp[0])))
	{
		free_tab_char(tmp);
		exit (0);
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
	data->colors[i_color] = tmp3[0][0] == '#' ? hex_to_rgb(tmp3[0]) : color_already_known(tmp3[0], data);
	recup_color_id(data, tmp2[0], i_color);
	free_3_tab_char(tmp, tmp2, tmp3);
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

int recup_pixel_color(t_data *data, int j, char *buff)
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
	return(j + 1);
}

void open_and_read_file(t_data *data)
{
	int fd;
	int ret;
	int i;
	int j;
	int token_before_img;
	char *buff;
	int i_color;

	i = 0;
	token_before_img = 0;
	j = 0;
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
				j = recup_pixel_color(data, j, buff);
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
