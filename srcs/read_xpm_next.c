/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_xpm_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 22:31:16 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/19 22:34:41 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

char *create_save_to_protect_c(t_data *data, char *str)
{
	char 	*color_char;
	int		i;

	i = 0;
	if(!(color_char = ft_strdup(str)))
		return (NULL);
	while(color_char[i])
	{
		if (i != (data->nb_char_pix + 1))
		{
			if (str[i] == 'c')
			{
				color_char[i] = '0';
				str[i] = 'a';
			}
			else
				color_char[i] = '1';
		}
		i++;
	}
	return(color_char);
}

/*
** fonction qui permet de trouver parmis toutes les couleurs du fichier la couleur du pixel
*/

int char_pixel_find(char *color_id, char *target, t_data *data, int x)
{
	int i;

	i = 0;
	while (i != data->nb_char_pix)
	{
		if (color_id[i] != target[x + 1])
			return (1);
		i++;
		x++;
	}
	return (0);
}

/*
** cette fonction permet de recuperer les couleurs pour un pixel donné en fonction de son caractere
*/

int find_color_for_pixel(t_data *data, char *c, char rvb, int x)
{
	int i;

	i = 0;
	while (i < data->nb_of_color)
	{
		if (char_pixel_find(data->colors[i].color_id, c, data, x) == 0)
		{
			if (rvb == 'r')
				return(data->colors[i].r);
			else if (rvb == 'v')
				return(data->colors[i].v);
			else if (rvb == 'b')
				return(data->colors[i].b);
		}
		i++;
	}
	return (0);
}
