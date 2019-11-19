/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:31:09 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/19 01:32:40 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int is_good_extension(char *str)
{
	int len;

	len = (int)ft_strlen(str) - 1;
	if (str[len] != 'm' || str[len - 1] != 'p')
		return (0);
	else if (str[len - 2] != 'x' || str[len - 3] != '.')
		return (0);
	return (1);
}

/*
** checking if 'statich char* ' is at the beginning of this line
*/

int check_begin_the_static_char(char *str)
{
	int ret;

	ret = 0;
	if (str[0] != 's' || str[1] != 't' || str[2] != 'a')
		ret = 1;
	if (str[3] != 't' || str[4] != 'i' || str[5] != 'c')
		ret = 1;
	if (str[6] != ' ' || str[11] != ' ' || str[12] != '*')
		ret = 1;
	if (str[7] != 'c' || str[8] != 'h' || str[9] != 'a' || str[10] != 'r')
		ret = 1;
	if (ret)
		ft_error(22, NULL);
	return (ret);
}

int check_the_static_char(char *str)
{
	int i;
	int end_nb;
	char *tmp;

	i = 13;
	if (ft_strlen(str) != 51)
		return(1);
	if (check_begin_the_static_char(str))
		return(1);
	end_nb = i + ft_strlen("a0053c01fccc4275c61107f5ef06391d");
	while (i != end_nb)
	{
		if (str[i] < 33 || str[i] > 126)
			return(1);
		i++;
	}
	if (!(tmp = ft_strdup("[] = {")))
		return (xpm_malloc_error("check_the_static_char"));
	end_nb = 0;
	while (str[i] && tmp[end_nb])
	{
		if (str[i] != tmp[end_nb])
			return (free_ret_1(tmp));
		i++;
		end_nb++;
	}
	free(tmp);
	return(str[i] ? 1 : 0);
}
