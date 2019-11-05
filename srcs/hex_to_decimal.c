/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:16:25 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/05 20:18:37 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"
#include <stdio.h>

int    test_base(const char c)
{
    int    nb;

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

t_color    hex_to_rgb(const char *str)
{
    int    	nb;
    int    	current;
    int 	str_base;
    int 	r;
    int 	g;
    int 	b;
    int 	i;
	t_color color;

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
        if (i == 2)
        {
            r = nb;
            nb = 0;
        }
        if (i == 4)
        {
            g = nb;
            nb = 0;
        }
        if (i == 6)
            b = nb;
    }
	color.r = r;
	color.v = g;
	color.b = b;
    return (color);
}
