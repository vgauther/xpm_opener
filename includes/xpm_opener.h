/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_opener.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 00:00:49 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/03 20:22:42 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_OPENER_H
# define XPM_OPENER_H

# include "../libft/includes/libft.h"


typedef struct 		s_color_known
{
	int 			r;
	int 			v;
	int 			b;
	char 			*name;
}					t_color_known;

typedef struct 		s_color
{
	int 			color_id;
	int 			r;
	int 			v;
	int 			b;
}					t_color;

typedef struct 		s_data
{
	char 		*file_name;
	char 		*file_content;
	int 		height_file;
	int 		width_file;
	int 		nb_of_color;
	int 		nb_char_pix;
	t_color 	*colors;
}					t_data;

void color_already_known(char *str);

#endif
