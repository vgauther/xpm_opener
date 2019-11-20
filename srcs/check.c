/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:31:09 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/20 16:55:54 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int		is_there_good_init_and_end_of_line(char *str)
{
	int len;

	len = ft_strlen(str) - 1;
	if (str[0] != '"' || str[len] != ',' || str[len - 1] != '"')
		return (1);
	return (0);
}

int		check_settings(char *str)
{
	char	**tmp;
	int		i;
	int		c;

	c = 0;
	i = 0;
	if (is_there_good_init_and_end_of_line(str))
		return (1);
	if (!(tmp = ft_strsplit(str, '"')))
		return (1);
	if (is_only_numeric_char(tmp[0]))
		return (xpm_free_tab_char_with_ret_1(tmp));
	if (tmp[0][0] == ' ')
		return (xpm_free_tab_char_with_ret_1(tmp));
	while (str[i])
	{
		if (i != 0 && str[i] == ' ' && str[i - 1] != ' ' && str[i + 1] != ' ')
			c++;
		else if (i != 0 && str[i] == ' ' &&
			(str[i - 1] == ' ' || str[i + 1] == ' '))
			return (xpm_free_tab_char_with_ret_1(tmp));
		i++;
	}
	xpm_free_tab_char(tmp);
	return (c != 4 ? 1 : 0);
}
