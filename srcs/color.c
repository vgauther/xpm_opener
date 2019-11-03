/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:41:12 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/03 20:55:10 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int structure_of_color(t_color_known *ck)
{
	/* red */
	ck[0].name = ft_strdup("red");
	ck[0].r = 255;
	ck[0].v = 0;
	ck[0].b = 0;

	/* green */
	ck[1].name = ft_strdup("green");
	ck[1].r = 0;
	ck[1].v = 255;
	ck[1].b = 0;

	/* blue */
	ck[2].name = ft_strdup("blue");
	ck[2].r = 0;
	ck[2].v = 0;
	ck[2].b = 255;

	/* white */
	ck[3].name = ft_strdup("white");
	ck[3].r = 255;
	ck[3].v = 255;
	ck[3].b = 255;

	/* black */
	ck[4].name = ft_strdup("black");
	ck[4].r = 0;
	ck[4].v = 0;
	ck[4].b = 0;

	/* orange */
	ck[5].name = ft_strdup("orange");
	ck[5].r = 100;
	ck[5].v = 65;
	ck[5].b = 0;

	/* magenta */
	ck[6].name = ft_strdup("magenta");
	ck[6].r = 100;
	ck[6].v = 0;
	ck[6].b = 100;

	/* cyan */
	ck[7].name = ft_strdup("cyan");
	ck[7].r = 0;
	ck[7].v = 100;
	ck[7].b = 100;

	/* yellow */
	ck[8].name = ft_strdup("yellow");
	ck[8].r = 100;
	ck[8].v = 100;
	ck[8].b = 0;

	/* gray */
	ck[8].name = ft_strdup("gray");
	ck[8].r = 75;
	ck[8].v = 75;
	ck[8].b = 75;

	/* dimgray */
	ck[8].name = ft_strdup("DimGray");
	ck[8].r = 75;
	ck[8].v = 75;
	ck[8].b = 75;
	return (8);
}

void color_already_known(char *str)
{
	t_color_known *ck;
	int nb_color;

	if (!(ck = malloc(sizeof(t_color_known) * 5)))
		exit(0);
	nb_color = structure_of_color(ck);
	while (nb_color >= 0)
	{
		if (ft_strcmp(ck[nb_color].name, str) == 0)
		{
			ft_putnbr(nb_color);
			ft_putstr(ck[nb_color].name);
		}
		nb_color--;
	}

}
