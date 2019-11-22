/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_xpm_settings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:08:20 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/22 12:15:08 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

/*
** recupere les donnes de la 3 lignes du fichier XPM
*/

void		recup_xpm_setting(t_data *data, char *str)
{
	char **tmp;
	char **tmp2;

	if ((tmp = ft_strsplit(str, '"')) == NULL)
	{
		xpm_malloc_error("recup_xpm_setting");
		exit(0);
	}
	if ((tmp2 = ft_strsplit(tmp[0], ' ')) == NULL)
	{
		xpm_free_tab_char(tmp);
		xpm_malloc_error("recup_xpm_setting");
		exit(0);
	}
	data->height_file = ft_atoi(tmp2[1]);
	data->width_file = ft_atoi(tmp2[0]);
	data->nb_of_color = ft_atoi(tmp2[2]);
	data->nb_char_pix = ft_atoi(tmp2[3]);
	xpm_free_tab_char(tmp);
	xpm_free_tab_char(tmp2);
	ft_messages(4, (void *)data);
}
