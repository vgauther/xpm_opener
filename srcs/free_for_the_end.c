/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_for_the_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 22:06:17 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/21 22:08:38 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

void			free_pixels(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->height_file)
	{
		free(data->pixel[i]);
		i++;
	}
	free(data->pixel);
}

void			free_color_built_in(t_data *data)
{
	int		i;

	i = 0;
	while (i < 235)
	{
		free(data->ck[i].name);
		i++;
	}
	free(data->ck);
}

void			free_colors(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_of_color)
	{
		free(data->colors[i].color_id);
		i++;
	}
	free(data->colors);
}
