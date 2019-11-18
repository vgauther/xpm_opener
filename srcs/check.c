/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:31:09 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/18 15:56:54 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int is_there_good_init_and_end_of_line(char *str)
{
	int len;

	len = ft_strlen(str) - 1;
	if (str[0] != '"' || str[len] != ',' || str[len - 1] != '"')
		return (1);
	return (0);
}

int check_settings(char *str)
{
	char **tmp;
	int i;
	int c;

	c = 0;
	i = 0;
	if (is_there_good_init_and_end_of_line(str))
		return(1);
	if (!(tmp = ft_strsplit(str, '"')))
		return (1);
	if (is_only_numeric_char(tmp[0]))
		return (free_tab_char_with_ret_1(tmp));
	if (tmp[0][0] == ' ')
		return (free_tab_char_with_ret_1(tmp));
	while(str[i])
	{
		if (i != 0 && str[i] == ' ' && str[i - 1] != ' ' && str[i + 1] != ' ')
			c++;
		else if (i != 0 && str[i] == ' ' && (str[i - 1] == ' ' || str[i + 1] == ' '))
			return (free_tab_char_with_ret_1(tmp));
		i++;
	}
	free_tab_char(tmp);
	if (c != 4)
		return (1);
	return (0);
}

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
			if (tmp[0][nb_char_for_pix + 4 + i] >= '0' && tmp[0][nb_char_for_pix + 4 + i] <= '9')
				i = i + 0;
			else if (tmp[0][nb_char_for_pix + 4 + i] >= 'A' && tmp[0][nb_char_for_pix + 4 + i] <= 'F')
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

int recup_char_for_pix_or_nb_of_color(char *str, int t)
{
	char **tmp;
	char **tmp2;
	int ret;

	if (!(tmp = ft_strsplit(str, '"')))
		return (1);
	if (!(tmp2 = ft_strsplit(tmp[0], ' ')))
		return (free_tab_char_with_ret_1(tmp));
	ret = 0;
	if (t == 1)
		ret = ft_atoi(tmp2[2]);
	else if (t == 0)
		ret = ft_atoi(tmp2[3]);
	else if (t == 3)
			ret = ft_atoi(tmp2[0]);
	else if (t == 2)
			ret = ft_atoi(tmp2[1]);
	free_tab_char(tmp);
	free_tab_char(tmp2);
	return(ret);
}

int is_this_a_good_pixel_line(char *str, t_data_chk *d)
{
	int i;
	int x;
	int c;
	char **tmp;

	i = 0;
	x = 0;
	c = 0;
	if(is_there_good_init_and_end_of_line(str))
	{
		if (d->height != d->height_count + 1)
			return (1);
		else if (d->height == d->height_count && str[d->nb_char_for_pix * d->width + 1] != '"')
			return (1);
	}
	if (!(tmp = ft_strsplit(str, '"')))
		return(1);
	if ((int)ft_strlen(tmp[0]) != (d->width * d->nb_char_for_pix))
		return (free_tab_char_with_ret_1(tmp));
	while (tmp[0][i])
	{
		c = 0;
		while(d->color_ids[x] && tmp[0][i] && d->color_ids[x] == tmp[0][i] && c < d->nb_char_for_pix)
		{
			c++;
			x++;
			i++;
		}
		if (c == d->nb_char_for_pix)
		{
			x = 0;
			i = i + d->nb_char_for_pix;
		}
		else if (x != 0 && d->color_ids[x] == 0 && d->color_ids[x - 1] != tmp[0][i - 1])
			return (free_tab_char_with_ret_1(tmp));
		else if (c == 0)
			x = x + d->nb_char_for_pix;
		else
			x = x - c + d->nb_char_for_pix;
		i = i - c;
	}
	free_tab_char(tmp);
	return (0);
}

int before_color(char *buff, t_data_chk *d)
{
	if (d->i == 0)
	{
		if (ft_strcmp(buff, "/* XPM */"))
			return (1);
	}
	if (d->i == 1)
	{
		if (check_the_static_char(buff))
 			return (1);
 	}
 	if (d->i == 2)
 	{
 		if (ft_strcmp(buff, "/* columns rows colors chars-per-pixel */"))
 			return (1);
 	}
 	if (d->i == 3)
 	{
 		if (check_settings(buff))
 			return(1);
 		if (!(d->color_ids = malloc_color_ids(buff)))
 			return (1);
 		d->nb_char_for_pix = recup_char_for_pix_or_nb_of_color(buff, 0);
 		d->nb_of_color = recup_char_for_pix_or_nb_of_color(buff, 1);
 		d->height = recup_char_for_pix_or_nb_of_color(buff, 2);
 		d->width = recup_char_for_pix_or_nb_of_color(buff, 3);
 		d->color_list_token = 2;
	}
	return (0);
}
