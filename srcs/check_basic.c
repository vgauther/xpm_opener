/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:31:09 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/19 22:36:47 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int is_good_extension(char *str)
{
	int len;

	if (str)
	{
		len = (int)ft_strlen(str) - 1;
		if (str[len] != 'm' || str[len - 1] != 'p')
			return (0);
		else if (str[len - 2] != 'x' || str[len - 3] != '.')
			return (0);
		return (1);
	}
	return (0);
}
