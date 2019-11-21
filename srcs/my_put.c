/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:13:28 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/21 15:14:41 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

void	ft_putstr2(char *str, char *str2)
{
	ft_putstr(str);
	ft_putstr(str2);
}

void	ft_putstr3(char *str, char *str2, char *str3)
{
	ft_putstr(str);
	ft_putstr(str2);
	ft_putstr(str3);
}

void	put3_i_13(int str, char *str2, int str3)
{
	ft_putnbr(str);
	ft_putstr(str2);
	ft_putnbr(str3);
}

void	put3_i_2(char *str, int str2, char *str3)
{
	ft_putstr(str);
	ft_putnbr(str2);
	ft_putstr(str3);
}
