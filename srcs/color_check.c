/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:41:12 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/21 20:56:53 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

static t_color_known	ch_ini_color_kn(char *r, char *v, char *b)
{
	t_color_known ck;

	ck.r = ft_atoi(r);
	ck.v = ft_atoi(v);
	ck.b = ft_atoi(b);
	return (ck);
}

static int				ch_structure_of_color(t_color_known *ck)
{
	t_read_var	rv;
	char		**tmp;
	char		**tmp1;
	int			i;

	i = 0;
	if ((rv.fd = open("data_color_built_in", O_RDONLY)) < 0)
		exit(0);
	while ((rv.ret = get_next_line(rv.fd, &rv.buff)))
	{
		tmp = ft_strsplit(rv.buff, ' ');
		tmp1 = ft_strsplit(tmp[1], ',');
		ck[i] = ch_ini_color_kn(tmp1[0], tmp1[1], tmp1[2]);
		ck[i].name = ft_strdup(tmp[0]);
		xpm_free_tab_char(tmp);
		xpm_free_tab_char(tmp1);
		free(rv.buff);
		i++;
	}
	close(rv.fd);
	return (234);
}

int						ch_color_already_known(char *str)
{
	t_color_known	*ck;
	int				nb_color;
	int				token;

	token = 1;
	if (!(ck = malloc(sizeof(t_color_known) * 235)))
		exit(0);
	nb_color = ch_structure_of_color(ck);
	while (nb_color >= 0)
	{
		if (ft_strcmp(ck[nb_color].name, str) == 0)
			token = 0;
		free(ck[nb_color].name);
		nb_color--;
	}
	free(ck);
	return (token);
}

/*
** cheching if chars in the color place of the are calling a built in color
*/

int						is_this_color_built_in(char *str, int nb_char)
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
	tmp = ft_strsplit(str, ' ');
	tok = ch_color_already_known(tmp[1]);
	xpm_free_tab_char(tmp);
	return (tok);
}
