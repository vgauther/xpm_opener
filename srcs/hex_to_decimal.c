/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:31:04 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/21 14:03:22 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int		test_base(const char c)
{
	int nb;

	if (c >= '0' && c <= '9')
		nb = c - '0';
	else if (c >= 'a' && c <= 'z')
		nb = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		nb = c - 'A' + 10;
	else
		nb = -1;
	return (nb);
}

int		color_attribution(t_color *color, int nb, int i)
{
	if (i == 2)
	{
		color->r = nb;
		nb = 0;
	}
	if (i == 4)
	{
		color->v = nb;
		nb = 0;
	}
	if (i == 6)
		color->b = nb;
	return (nb);
}

t_color	hex_to_rgb(const char *str)
{
	int			nb;
	int			current;
	int			str_base;
	int			i;
	t_color		color;

	i = 0;
	str_base = 16;
	nb = 0;
	str++;
	current = test_base(*str);
	while (current >= 0 && current < str_base)
	{
		i++;
		nb = nb * str_base + current;
		str++;
		current = test_base(*str);
		nb = color_attribution(&color, nb, i);
	}
	return (color);
}
