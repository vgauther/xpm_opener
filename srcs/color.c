/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:41:12 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/05 22:20:40 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int structure_of_color(t_color_known *ck)
{
	int fd;
	int ret;
	char *buff;
	char **tmp;
	char **tmp1;

	int i;

	i = 0;
	fd = open("data_color_built_in", O_RDONLY);

	if (fd < 0)
		exit(0);
	while ((ret = get_next_line(fd, &buff)))
	{

		tmp = ft_strsplit(buff, ' ');
		ck[i].name = ft_strdup(tmp[0]);
		tmp1 = ft_strsplit(tmp[1], ',');
		ft_putstr(tmp1[1]);
		ft_putstr("\n");

		ck[i].r = ft_atoi(tmp1[0]);
		ck[i].v = ft_atoi(tmp1[1]);
		ck[i].b = ft_atoi(tmp1[2]);
		free_tab_char(tmp);
		free_tab_char(tmp1);
		free(buff);
		i++;
	}
	return (234);
}

t_color color_already_known(char *str)
{
	t_color_known *ck;
	int nb_color;
	t_color color;

	if (!(ck = malloc(sizeof(t_color_known) * 235)))
		exit(0);
	nb_color = structure_of_color(ck);
	while (nb_color >= 0)
	{
		if (ft_strcmp(ck[nb_color].name, str) == 0)
		{
			color.r = ck[nb_color].r;
			color.v = ck[nb_color].v;
			color.b = ck[nb_color].b;
			return(color);
		}
		nb_color--;
	}
	color.r = 0;
	color.v = 0;
	color.b = 0;
	return(color);
}
