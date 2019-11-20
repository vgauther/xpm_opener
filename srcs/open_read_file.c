/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:39:43 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/20 17:39:49 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

static void	init_var_for_open_read_file(int *i, int *j, int *tok, int *i_c)
{
	*i = 0;
	*j = 0;
	*tok = 0;
	*i_c = 0;
}

void		open_and_read_file(t_data *data)
{
	t_read_var	rv;
	int			i;
	int			j;
	int			token_before_img;
	int			i_color;

	init_var_for_open_read_file(&i, &j, &token_before_img, &i_color);
	if ((rv.fd = open(data->file_name, O_RDONLY)) < 0)
		exit(0);
	while ((rv.ret = get_next_line(rv.fd, &rv.buff)))
	{
		if (i == 3)
			xpm_setting(data, rv.buff);
		if (i > 3 && token_before_img == 1 && rv.buff[0] == '"')
			j = recup_pixel_color(data, j, rv.buff);
		if (i > 3 && rv.buff[0] == '/' && token_before_img == 0)
			token_before_img = 1;
		if (i > 3 && token_before_img == 0)
		{
			recup_colors(data, rv.buff, i_color);
			i_color++;
		}
		free(rv.buff);
		i++;
	}
}
