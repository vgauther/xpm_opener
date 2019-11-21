/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:41:12 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/21 20:58:59 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

static t_color_known	ini_color_kn(char *r, char *v, char *b)
{
	t_color_known ck;

	ck.r = ft_atoi(r);
	ck.v = ft_atoi(v);
	ck.b = ft_atoi(b);
	return (ck);
}

int						structure_of_color(t_data *data)
{
	t_read_var	rv;
	char		**tmp;
	char		**tmp1;
	int			i;

	i = 0;
	if ((rv.fd = open("data_color_built_in", O_RDONLY)) < 0)
		return (xpm_fd_error("structure_of_color"));
	while ((rv.ret = get_next_line(rv.fd, &rv.buff)))
	{
		if (!(tmp = ft_strsplit(rv.buff, ' ')))
			return (xpm_malloc_error("structure_of_color"));
		if (!(tmp1 = ft_strsplit(tmp[1], ',')))
			return (xpm_malloc_error("structure_of_color"));
		data->ck[i] = ini_color_kn(tmp1[0], tmp1[1], tmp1[2]);
		data->ck[i].name = ft_strdup(tmp[0]);
		xpm_free_tab_char(tmp);
		xpm_free_tab_char(tmp1);
		free(rv.buff);
		i++;
	}
	close(rv.fd);
	return (0);
}

static t_color			ini_color(int r, int v, int b)
{
	t_color c;

	c.r = r;
	c.v = v;
	c.b = b;
	return (c);
}

t_color					color_already_known(char *str, t_data *d)
{
	int			nb_color;

	nb_color = 234;
	while (nb_color >= 0)
	{
		if (ft_strcmp(d->ck[nb_color].name, str) == 0)
		{
			return (ini_color(d->ck[nb_color].r, d->ck[nb_color].v,
				d->ck[nb_color].b));
		}
		nb_color--;
	}
	return (ini_color(0, 0, 0));
}
