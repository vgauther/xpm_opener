/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 23:36:49 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/06 15:53:22 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

void sdl_messages(int id)
{
	if (id == -1)
	{
		ft_putstr("\n[✓] SDL Inited");

	}
	else if (id == -2)
	{
		ft_putstr("[✓] Window created");
	}
	else if (id == -3)
	{
		ft_putstr("[✓] Renderer created");
	}
	else if (id == -4)
	{
		ft_putstr("\nPrinting pixels on the renderer..");
	}
	else if (id == -5)
	{
		ft_putstr("\n[✓] Printing done");
	}
	else if (id == -6)
	{
		ft_putstr("\n[✓] XPM Image displayed\n");
	}
	ft_putstr("\n");
}

void ft_messages(int id, void *data)
{
	t_data *d;

	if (id < 0)
	{
		sdl_messages(id);
		return ;
	}
	if (id == 1)
	{
		ft_putstr("\nAnalysis in progress for : ");
		ft_putstr((char *)data);
		ft_putstr("\n");

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
	else if (id == 5)
	{
		ft_putstr("\n - Starting the work on the XPM ..\n");
	}
	else if (id == 6)
	{
		ft_putstr("\nRESULT : The file looks to be an XPM file 0 error detected\n");
	}
	else if (id == 7)
	{
		ft_putstr("[✓] The file is well built and formated");
	}
	else if (id == 8)
	{
		ft_putstr("[✓] The file is made with only authorized chars");
	}
	else if (id == 12)
		ft_putstr("[✓] Recovery of built in colors done");
	ft_putstr("\n");
}

void ft_error(int id, void *data)
{
	ft_putstr("\n\x1b[31m");
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
	else if (id == 5)
	{
		ft_putstr("error : ");
		ft_putstr("file is null or empty");
	}
	else if (id == 6)
	{
		ft_putstr("error : we wanted `/* pixels */` and we have`");
		ft_putstr((char *)data);
		ft_putstr("`");
	}
	else if (id == 7)
	{
		ft_putstr("error : we don't count the same number of colors as writted in the file");
	}
	else if (id == 8)
	{
		ft_putstr("error : must have quote and comma on the side of a line");
	}
	else if (id == 10)
	{
		ft_putstr("error : the line ");
		ft_putstr(ft_itoa((int)data));
		ft_putstr("is not well formated");

	}
	else if (id == 22)
	{
		ft_putstr("error : 'static char *' wasn't found on line 2");
	}
	else
		ft_putstr("error");
	ft_putstr("\x1b[0m\n\n");
}
