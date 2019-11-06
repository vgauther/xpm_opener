/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 23:36:49 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/05 23:54:27 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

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
	else if (id == 3)
	{
		ft_putstr("error : ");
		ft_putstr("one of the char is not valid");
	}
	else if (id == 4)
	{
		ft_putstr("error : ");
		ft_putstr("extension is not valid");
	}
	else
		ft_putstr("error");
	ft_putstr("\n");
}
