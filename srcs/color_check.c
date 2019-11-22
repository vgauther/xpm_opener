/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:41:12 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/22 14:18:58 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int						ch_color_already_known(char *str, t_data *data)
{
	int				nb_color;

	nb_color = 234;
	while (nb_color >= 0)
	{
		if (ft_strcmp(data->ck[nb_color].name, str) == 0)
			return (0);
		nb_color--;
	}
	return (1);
}

/*
** cheching if chars in the color place of the are calling a built in color
*/

int						is_this_color_built_in(char *str, int nb_char,
						t_data *data)
{
	int		i;
	char	**tmp;
	int		tok;

	i = 0;
	while (i < nb_char + 1 && str[i])
	{
		str[i] = '1';
		i++;
	}
	if ((tmp = ft_strsplit(str, ' ')) == NULL)
		return (xpm_malloc_error("is_this_color_built_in"));
	tok = ch_color_already_known(tmp[1], data);
	xpm_free_tab_char(tmp);
	return (tok);
}
