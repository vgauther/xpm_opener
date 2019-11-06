/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_opener.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 00:00:49 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/06 12:04:15 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_OPENER_H
# define XPM_OPENER_H

# include "../libft/includes/libft.h"
# include "SDL2/SDL.h"

typedef struct 		s_pixel
{
	int 			r;
	int 			v;
	int 			b;
}					t_pixel;

typedef struct 		s_color_known
{
	int 			r;
	int 			v;
	int 			b;
	char 			*name;
}					t_color_known;

typedef struct 		s_color
{
	char* 			color_id;
	int 			r;
	int 			v;
	int 			b;
}					t_color;

typedef struct 		s_data
{
	char 		*file_name;
	int 		height_file;
	int 		width_file;
	int 		nb_of_color;
	int 		nb_char_pix;
	t_color 	*colors;
	t_pixel		**pixel;
}					t_data;

t_color 	color_already_known(char *str);
t_color    	hex_to_rgb(const char *str);
void 		free_tab_char(char **tab);
void 		print_image(t_data *data);
int 		is_good_extension(char *str);
int 		is_the_file_ok(t_data *data);
void 		ft_messages(int id, void *data);
void 		ft_error(int id, void *data);
int 		ch_color_already_known(char *str);

#endif
