/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construction_of_color_line.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:25:05 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/22 14:11:57 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int		is_a_hexa_char(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	else if (c >= 'A' && c <= 'F')
		return (0);
	else if (c == '#')
		return (0);
	return (1);
}

int		check_contruction_color_line(char **tmp, int nb_char_for_pix)
{
	int i;

	i = 0;
	while (i < 6 && tmp[0][nb_char_for_pix + 4 + i])
	{
		if (is_a_hexa_char(tmp[0][nb_char_for_pix + 4 + i]) != 0)
			return (1);
		i++;
	}
	if (i != 6)
		return (1);
	return (0);
}

int		construction_of_color_line(char *str, int nb_char_for_pix, t_data *data)
{
	char	**tmp;

	if ((int)ft_strlen(str) < nb_char_for_pix)
		return (1);
	if (!(tmp = ft_strsplit(str, '"')))
		return (1);
	if (tmp[0][nb_char_for_pix + 1] != 'c')
		return (xpm_free_tab_char_with_ret_1(tmp));
	if (tmp[0][nb_char_for_pix + 1] == 'c' && (tmp[0][nb_char_for_pix] != ' '
	|| tmp[0][nb_char_for_pix + 2] != ' '))
		return (xpm_free_tab_char_with_ret_1(tmp));
	if (tmp[0][nb_char_for_pix + 3] != '#')
	{
		if ((is_this_color_built_in(tmp[0], nb_char_for_pix, data)))
			return (xpm_free_tab_char_with_ret_1(tmp));
	}
	else
	{
		if (check_contruction_color_line(tmp, nb_char_for_pix))
			return (xpm_free_tab_char_with_ret_1(tmp));
	}
	xpm_free_tab_char(tmp);
	return (0);
}
