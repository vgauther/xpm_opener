/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_construction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:00:32 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/22 14:24:02 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

static int	local_message(int i, char *str)
{
	ft_putstr("\n\x1b[31m");
	if (i == 0)
	{
		ft_putstr("error : we don't count the same number ");
		ft_putstr("of colors as writted in the file");
	}
	else if (i == 1)
	{
		ft_putstr("error : we wanted `/* pixels */` and we have`");
		ft_putstr(str);
		ft_putstr("`");
	}
	else if (i == 2)
		ft_putstr("error : must have quote and comma on the side of a line");
	else if (i == 3)
	{
		ft_putstr("error : the line ");
		ft_putstr(str);
		ft_putstr("is not well formated");
	}
	return (1);
}

int			set_var_check_zero(t_data_chk *d, int *j)
{
	d->color_list_token = 0;
	d->color_count = 0;
	d->height_count = 0;
	*j = 0;
	d->i = 0;
	return (0);
}

int			check_the_construction3(t_data_chk *d, char *buff)
{
	if (buff[0] == '"')
	{
		if (is_this_a_good_pixel_line(buff, d))
			return (1);
	}
	else
	{
		if (ft_strcmp(buff, "};"))
			return (1);
	}
	d->height_count++;
	return (0);
}

int			check_the_constr2(char *buff, t_data_chk *d, t_data *data)
{
	if (buff[0] == '/')
	{
		if (d->color_count != d->nb_of_color)
			return (local_message(0, NULL));
		if (ft_strcmp(buff, "/* pixels */"))
			return (local_message(1, buff));
		d->color_ids[d->j2] = 0;
		d->color_list_token = 3;
	}
	else
	{
		if (is_there_good_init_and_end_of_line(buff))
			return (local_message(2, NULL));
		if (construction_of_color_line(buff, d->nb_char_for_pix, data))
			return (local_message(10, ft_itoa(d->i)));
		d->j = 0;
		while (d->j != d->nb_char_for_pix)
		{
			d->color_ids[d->j2] = buff[d->j + 1];
			d->j = d->j + 1;
			d->j2 = d->j2 + 1;
		}
		d->color_count++;
	}
	return (0);
}

int			check_the_construction(char *name_file, t_data *data)
{
	char		*buff;
	int			ret;
	t_data_chk	d;

	d.j2 = set_var_check_zero(&d, &d.j);
	if ((d.fd = open(name_file, O_RDONLY)) < 0)
		return (1);
	while ((ret = get_next_line(d.fd, &buff)))
	{
		if (d.i < 4 && before_color(buff, &d))
			return (1);
		if (d.color_list_token == 3 && check_the_construction3(&d, buff) == 1)
			return (1);
		else if (d.color_list_token == 1 &&
			check_the_constr2(buff, &d, data))
			return (1);
		d.color_list_token = d.color_list_token == 2 ? 1 : d.color_list_token;
		d.i++;
		free(buff);
	}
	close(d.fd);
	free(d.color_ids);
	return (0);
}
