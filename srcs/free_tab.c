/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:17:06 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/11 17:46:14 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

void free_tab_char(char **tab)
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

void free_2_tab_char(char **tab, char **tab1)
{
	free_tab_char(tab);
	free_tab_char(tab1);
}

void free_3_tab_char(char **tab, char **tab1, char **tab2)
{
	free_tab_char(tab);
	free_tab_char(tab1);
	free_tab_char(tab2);
}
