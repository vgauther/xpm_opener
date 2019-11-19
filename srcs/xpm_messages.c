/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_messages.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 01:15:01 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/19 01:33:44 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int xpm_fd_error(char *str)
{
	ft_putstr("XPM LOAD FD ERROR : program quit in the function");
	ft_putstr(str);
	ft_putstr(".\n");
	return (1);
}

int xpm_malloc_error(char *str)
{
	ft_putstr("XPM LOAD MALLOC ERROR : program quit in the function");
	ft_putstr(str);
	ft_putstr(".\n");
	return (1);
}
