/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 22:38:29 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/20 19:21:19 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

char		*malloc_color_ids(char *str)
{
	char	**tmp;
	char	**tmp2;
	char	*color_ids;
	int		mal;

	if (!(tmp = ft_strsplit(str, '"')))
		return (NULL);
	if (!(tmp2 = ft_strsplit(tmp[0], ' ')))
	{
		xpm_free_tab_char(tmp);
		return (NULL);
	}
	mal = ft_atoi(tmp2[2]) * ft_atoi(tmp2[3]) + 1;
	if (!(color_ids = malloc(sizeof(char) * mal)))
	{
		xpm_free_tab_char(tmp);
		xpm_free_tab_char(tmp2);
		return (NULL);
	}
	xpm_free_tab_char(tmp);
	xpm_free_tab_char(tmp2);
	return (color_ids);
}

int			recup_char_for_pix_or_nb_of_color(char *str, int t)
{
	char	**tmp;
	char	**tmp2;
	int		ret;

	if (!(tmp = ft_strsplit(str, '"')))
		return (1);
	if (!(tmp2 = ft_strsplit(tmp[0], ' ')))
		return (xpm_free_tab_char_with_ret_1(tmp));
	ret = 0;
	if (t == 1)
		ret = ft_atoi(tmp2[2]);
	else if (t == 0)
		ret = ft_atoi(tmp2[3]);
	else if (t == 3)
		ret = ft_atoi(tmp2[0]);
	else if (t == 2)
		ret = ft_atoi(tmp2[1]);
	xpm_free_tab_char(tmp);
	xpm_free_tab_char(tmp2);
	return (ret);
}

static int is_this_a_good_pixel_cond(int c, int *x, int *i, t_data_chk *d, char **tmp)
{
	if (c == d->nb_char_for_pix)
	{
		*x = 0;
		*i = *i + d->nb_char_for_pix;
	}
	else if (*x != 0 && d->color_ids[*x] == 0 &&
		d->color_ids[*x - 1] != tmp[0][*i - 1])
		return (xpm_free_tab_char_with_ret_1(tmp));
	else if (c == 0)
		*x = *x + d->nb_char_for_pix;
	else
		*x = *x - c + d->nb_char_for_pix;
	return (0);
}

static int	is_this_a_good_pixel_looking(char **tmp, t_data_chk *d)
{
	int		c;
	int		x;
	int		i;

	i = 0;
	x = 0;
	while (tmp[0][i])
	{
		c = 0;
		while (d->color_ids[x] && tmp[0][i] && d->color_ids[x] == tmp[0][i] &&
			c < d->nb_char_for_pix)
		{
			c++;
			x++;
			i++;
		}
		if (is_this_a_good_pixel_cond(c, &x, &i, d, tmp))
			return (1);
		
		i = i - c;
	}
	return (0);
}

int			is_this_a_good_pixel_line(char *str, t_data_chk *d)
{
	char	**tmp;

	if (is_there_good_init_and_end_of_line(str))
	{
		if (d->height != d->height_count + 1)
			return (1);
		else if (d->height == d->height_count && str[d->nb_char_for_pix * d->width + 1] != '"')
			return (1);
	}
	if (!(tmp = ft_strsplit(str, '"')))
		return (1);
	if ((int)ft_strlen(tmp[0]) != (d->width * d->nb_char_for_pix))
		return (xpm_free_tab_char_with_ret_1(tmp));
	is_this_a_good_pixel_looking(tmp, d);
	xpm_free_tab_char(tmp);
	return (0);
}
