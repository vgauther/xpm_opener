/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:58:12 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/12 15:31:50 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int is_only_numeric_char(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int is_a_hexa_char(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	else if (c >= 'A' && c <= 'F')
		return (0);
	return (1);
}
