/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:31:09 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/04 16:46:11 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int is_good_extension(char *str)
{
	int len;

	len = ft_strlen(str);
	if (str[len] != 'm' || str[len - 1] != 'p' || str[len] != 'x' || str[len] != '.')
	{
		return (0);
	}
	return (1);
}
