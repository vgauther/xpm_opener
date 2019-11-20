/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the_static_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:01:45 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/19 12:10:24 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

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
		xpm_error(22, NULL);
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
		return (1);
	end_nb = 0;
	while (str[i] && tmp[end_nb])
	{
		if (str[i] != tmp[end_nb])
		{
			free(tmp);
			return (1);
		}
		i++;
		end_nb++;
	}
	free(tmp);
	return(str[i] ? 1 : 0);
}
