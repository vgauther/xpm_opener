/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:42:54 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/21 17:57:04 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

/*
** cette fonction permet de creer une structure contenan une des
** couleurs en debut de fichier
*/

t_color		attribution_color(char **tmp2, t_data *data)
{
	t_color c;
	char	**tmp3;

	if (!(tmp3 = ft_strsplit(tmp2[1], ' ')))
		exit(0);
	c = tmp3[0][0] == '#' ? hex_to_rgb(tmp3[0]) :
	color_already_known(tmp3[0], data);
	return (c);
}

int			recup_colors(t_data *data, char *str, int i_color)
{
	char	**tmp;
	char	**tmp2;
	char	*color_char;
	int		i;

	if (!(tmp = ft_strsplit(str, '"')))
		return (xpm_malloc_error("recup_colors"));
	if (!(color_char = create_save_to_protect_c(data, tmp[0])))
	{
		xpm_free_tab_char(tmp);
		exit(0);
	}
	if (!(tmp2 = ft_strsplit(tmp[0], 'c')))
		return (xpm_malloc_error("recup_colors"));
	i = 0;
	while (i != (data->nb_char_pix + 1))
	{
		if (color_char[i] == '0')
			tmp2[0][i] = 'c';
		i++;
	}
	i++;
	while (color_char[i])
	{
		if (color_char[i] == '0')
			tmp2[1][i - data->nb_char_pix + 1] = 'c';
		i++;
	}
	data->colors[i_color] = attribution_color(tmp2, data);
	recup_color_id(data, tmp2[0], i_color);
	xpm_free_2_tab_char(tmp, tmp2);
	free(color_char);
	return (0);
}

/*
** recupere les donnes de la 3 lignes du fichier XPM
*/

void		recup_xpm_setting(t_data *data, char *str)
{
	char **tmp;
	char **tmp2;

	tmp = ft_strsplit(str, '"');
	tmp2 = ft_strsplit(tmp[0], ' ');
	data->height_file = ft_atoi(tmp2[1]);
	data->width_file = ft_atoi(tmp2[0]);
	data->nb_of_color = ft_atoi(tmp2[2]);
	data->nb_char_pix = ft_atoi(tmp2[3]);
	xpm_free_tab_char(tmp);
	xpm_free_tab_char(tmp2);
	ft_messages(4, (void *)data);
}

/*
** alloue une str pour le color_id afin de reperer cette couleur
** parmis les pixels
*/

void		recup_color_id(t_data *data, char *str, int i_color)
{
	int i;

	i = 0;
	if (!(data->colors[i_color].color_id = malloc(sizeof(char) * (data->nb_char_pix + 1))))
		exit(0);
	while (i != data->nb_char_pix)
	{
		data->colors[i_color].color_id[i] = str[i];
		i++;
	}
	data->colors[i_color].color_id[i] = 0;
}
