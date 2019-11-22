/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:29:39 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/22 12:56:40 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

static t_color_known	ini_color_kn(char *r, char *v, char *b)
{
	t_color_known ck;

	ck.r = ft_atoi(r);
	ck.v = ft_atoi(v);
	ck.b = ft_atoi(b);
	return (ck);
}

int						xmp_init_structure_of_color(t_xpm_init *data)
{
	t_read_var	rv;
	char		**tmp;
	char		**tmp1;
	int			i;

	i = 0;
	if ((rv.fd = open("data_color_built_in", O_RDONLY)) < 0)
		return (xpm_fd_error("structure_of_color"));
	while ((rv.ret = get_next_line(rv.fd, &rv.buff)))
	{
		if (!(tmp = ft_strsplit(rv.buff, ' ')))
			return (xpm_malloc_error("structure_of_color"));
		if (!(tmp1 = ft_strsplit(tmp[1], ',')))
			return (xpm_malloc_error("structure_of_color"));
		data->ck[i] = ini_color_kn(tmp1[0], tmp1[1], tmp1[2]);
		data->ck[i].name = ft_strdup(tmp[0]);
		xpm_free_tab_char(tmp);
		xpm_free_tab_char(tmp1);
		free(rv.buff);
		i++;
	}
	close(rv.fd);
	return (0);
}

void					init_xpm(t_xpm_init *xpm)
{
	if (!(xpm->ck = malloc(sizeof(t_color_known) * (235))))
		exit(0);
	if (xmp_init_structure_of_color(xpm))
		exit(0);
}
