/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:39:43 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/19 22:31:49 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

/*
** comme le char `c` est present dans les string qui definissent les pixels
** on doit proteger le strsplit en enlevant tout les c autres que celui
** qui separe l'id de la couleur
*/

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

int recup_all_built_in_color(t_data *data)
{
	if (!(data->ck = malloc(sizeof(t_color_known) * (235))))
		return (1);
	structure_of_color(data);
	return (0);
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
