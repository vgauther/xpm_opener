/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:31:09 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/20 17:49:37 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

static void		fill_before_color(t_data_chk *d, char *buff)
{
	d->nb_char_for_pix = recup_char_for_pix_or_nb_of_color(buff, 0);
	d->nb_of_color = recup_char_for_pix_or_nb_of_color(buff, 1);
	d->height = recup_char_for_pix_or_nb_of_color(buff, 2);
	d->width = recup_char_for_pix_or_nb_of_color(buff, 3);
	d->color_list_token = 2;
}

int				before_color(char *buff, t_data_chk *d)
{
	if (d->i == 0)
	{
		if (ft_strcmp(buff, "/* XPM */"))
			return (1);
	}
	if (d->i == 1)
	{
		if (check_the_static_char(buff))
			return (1);
	}
	if (d->i == 2)
	{
		if (ft_strcmp(buff, "/* columns rows colors chars-per-pixel */"))
			return (1);
	}
	if (d->i == 3)
	{
		if (check_settings(buff))
			return (1);
		if (!(d->color_ids = malloc_color_ids(buff)))
			return (1);
		fill_before_color(d, buff);
	}
	return (0);
}
