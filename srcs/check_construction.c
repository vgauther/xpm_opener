/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_construction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:00:32 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/12 14:26:06 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int set_var_check_zero(t_data_chk *d, int *j)
{
	d->color_list_token = 0;
	d->color_count = 0;
	d->height_count = 0;
	*j = 0;
	d->i = 0;
	return (0);
}

int check_the_construction2(char *buff, t_data_chk *d, int *j2, int *j)
{
	if (buff[0] == '/')
	{
		if (d->color_count != d->nb_of_color)
		{
			ft_error(7, NULL);
			return (1);
		}
		if(ft_strcmp(buff, "/* pixels */"))
		{
			ft_error(6, buff);
			return(1);
		}
		d->color_ids[*j2] = 0;
		d->color_list_token = 3;
	}
	else
	{
		if(is_there_good_init_and_end_of_line(buff))
		{
			ft_error(8, &d->i);
			return (1);
		}
		if (construction_of_color_line(buff, d->nb_char_for_pix))
		{
			ft_error(10, &d->i);
			return (1);
		}
		*j = 0;
		while (*j != d->nb_char_for_pix)
		{
			d->color_ids[*j2] = buff[*j + 1];
			*j = *j + 1;
			*j2 = *j2 + 1;
		}
		d->color_count++;
	}
	return (0);
}

int check_the_construction(char *name_file)
{
	char *buff;
	int ret;
	int j;
	int j2;
	t_data_chk d;

	j2 = set_var_check_zero(&d, &j);
	if ((d.fd = open(name_file, O_RDONLY)) < 0)
		return (1);
	while ((ret = get_next_line(d.fd, &buff)))
	{
		if (d.i < 4 && before_color(buff, &d))
				return (1);
		if (d.color_list_token == 3)
		{
			if (buff[0] == '"')
			{
				if(is_this_a_good_pixel_line(buff, &d))
				{
					ft_putstr("-55-\n");
					return (1);
				}
			}
			else
			{
				if(ft_strcmp(buff, "};"))
					return (1);
			}
			d.height_count++;
		}
		else if (d.color_list_token == 1 && check_the_construction2(buff, &d, &j2, &j))
			return(1);
		d.color_list_token = d.color_list_token == 2 ? 1 : d.color_list_token;
		d.i++;
		free(buff);
	}
	close(d.fd);
	free(d.color_ids);
	return(0);
}
