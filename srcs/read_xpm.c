/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:39:43 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/22 12:53:39 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

/*
** comme le char `c` est present dans les string qui definissent les pixels
** on doit proteger le strsplit en enlevant tout les c autres que celui
** qui separe l'id de la couleur
*/

void	xpm_setting(t_data *data, char *buff)
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

int		recup_pixel_color(t_data *data, int j, char *buff)
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
	return (j + 1);
}

int		recup_all_built_in_color(t_data *data)
{
	if (!(data->ck = malloc(sizeof(t_color_known) * (235))))
		return (1);
	structure_of_color(data);
	return (0);
}

void	read_xpm(char *name, t_data *data, t_xpm_init xpm)
{
	data->file_name = ft_strdup(name);
	ft_messages(1, (void *)data->file_name);
	data->ck = xpm.ck;
	ft_messages(12, NULL);
	ft_messages(5, NULL);
	is_the_file_ok(data);
	ft_messages(6, NULL);
	open_and_read_file(data);
}
