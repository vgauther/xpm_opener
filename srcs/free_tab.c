/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:17:06 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/20 18:22:35 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

void	xpm_free_tab_char(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	xpm_free_2_tab_char(char **tab, char **tab1)
{
	xpm_free_tab_char(tab);
	xpm_free_tab_char(tab1);
}

void	xpm_free_3_tab_char(char **tab, char **tab1, char **tab2)
{
	xpm_free_tab_char(tab);
	xpm_free_tab_char(tab1);
	xpm_free_tab_char(tab2);
}

int		xpm_free_tab_char_with_ret_1(char **tab)
{
	xpm_free_tab_char(tab);
	return (1);
}
