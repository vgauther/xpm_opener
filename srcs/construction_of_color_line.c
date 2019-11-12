/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construction_of_color_line.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:25:05 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/12 15:33:43 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

char *malloc_color_ids(char *str)
{
	char **tmp;
	char **tmp2;
	char *color_ids;
	int mal;

	if (!(tmp = ft_strsplit(str, '"')))
		return (NULL);
	if (!(tmp2 = ft_strsplit(tmp[0], ' ')))
	{
		free_tab_char(tmp);
		return (NULL);
	}
	mal = ft_atoi(tmp2[2]) * ft_atoi(tmp2[3]) + 1;
	if (!(color_ids = malloc(sizeof(char) * mal)))
	{
		free_tab_char(tmp);
		free_tab_char(tmp2);
		return (NULL);
	}
	free_tab_char(tmp);
	free_tab_char(tmp2);
	return(color_ids);
}

int construction_of_color_line(char *str, int nb_char_for_pix)
{
	char **tmp;
	int i;

	i = 0;
	if ((int)ft_strlen(str) < nb_char_for_pix)
		return (1);
	if (!(tmp = ft_strsplit(str, '"')))
		return (1);
	if (tmp[0][nb_char_for_pix + 1] != 'c')
		return (free_tab_char_with_ret_1(tmp));
	if (tmp[0][nb_char_for_pix + 1] == 'c' && (tmp[0][nb_char_for_pix] != ' ' || tmp[0][nb_char_for_pix + 2] != ' '))
		return (free_tab_char_with_ret_1(tmp));
	if (tmp[0][nb_char_for_pix + 3] != '#')
	{
		if ((is_this_color_built_in(tmp[0], nb_char_for_pix)))
			return (free_tab_char_with_ret_1(tmp));
	}
	else
	{
		while (i < 6 && tmp[0][nb_char_for_pix + 4 + i])
		{
			if (is_a_hexa_char(tmp[0][nb_char_for_pix + 4 + i]))
				i = i + 0;
			else
				return (free_tab_char_with_ret_1(tmp));
			i++;
		}
		if (i != 6)
			return (free_tab_char_with_ret_1(tmp));
	}
	free_tab_char(tmp);
	return (0);
}
