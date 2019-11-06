/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:31:09 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/06 15:51:51 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int free_tab_char_with_ret_1(char **tab)
{
	free_tab_char(tab);
	return (1);
}

int is_good_extension(char *str)
{
	int len;

	len = (int)ft_strlen(str) - 1;
	if (str[len] != 'm' || str[len - 1] != 'p')
		return (0);
	else if (str[len - 2] != 'x' || str[len - 3] != '.')
		return (0);
	return (1);
}

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
		ft_error(22, NULL);
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
	tmp = ft_strdup("[] = {");
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
	if (str[i])
		return(1);
	return(0);
}

//"128 128 1 1 ",

int is_there_good_init_and_end_of_line(char *str)
{
	int len;

	len = ft_strlen(str) - 1;
	if (str[0] != '"' || str[len] != ',' || str[len - 1] != '"')
		return (1);
	return (0);
}

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

int check_settings(char *str)
{
	char **tmp;
	int i;
	int c;

	c = 0;
	i = 0;
	if (is_there_good_init_and_end_of_line(str))
		return(1);
	tmp = ft_strsplit(str, '"');
	if (is_only_numeric_char(tmp[0]))
	{
		free_tab_char(tmp);
		return (1);
	}
	if (tmp[0][0] == ' ')
	{
		free_tab_char(tmp);
		return (1);
	}
	while(str[i])
	{
		if (i != 0 && str[i] == ' ' && str[i - 1] != ' ' && str[i + 1] != ' ')
			c++;
		else if (i != 0 && str[i] == ' ' && (str[i - 1] == ' ' || str[i + 1] == ' '))
		{
			free_tab_char(tmp);
			return (1);
		}
		i++;
	}
	free_tab_char(tmp);
	if (c != 4)
		return (1);
	return (0);
}

char *malloc_color_ids(char *str)
{
	char **tmp;
	char **tmp2;
	char *color_ids;
	int mal;

	tmp = ft_strsplit(str, '"');
	tmp2 = ft_strsplit(tmp[0], ' ');
	mal = ft_atoi(tmp2[2]) * ft_atoi(tmp2[3]) + 1;
	if (!(color_ids = malloc(sizeof(char) * mal)))
	{
		free_tab_char(tmp);
		free_tab_char(tmp2);
		return (NULL);
	}
	free_tab_char(tmp);
	free_tab_char(tmp2);
	return(color_ids);
}

/*
** cheching if chars in the color place of the are calling a built in color
*/

int is_this_color_built_in(char *str, int nb_char)
{
	int i;
	char **tmp;
	int tok;

	i = 0;
	while (i < nb_char + 1 && str[i])
	{
		str[i] = '1';
		i++;
	}
	tmp = ft_strsplit(str, ' ');
	tok = ch_color_already_known(tmp[1]);
	free_tab_char(tmp);
	return (tok);
}

int construction_of_color_line(char *str, int nb_char_for_pix)
{
	char **tmp;
	int i;

	i = 0;
	if ((int)ft_strlen(str) < nb_char_for_pix)
		return(1);
	tmp = ft_strsplit(str, '"');
	if (tmp[0][nb_char_for_pix + 1] != 'c')
		return (free_tab_char_with_ret_1(tmp));
	if (tmp[0][nb_char_for_pix + 1] == 'c' && (tmp[0][nb_char_for_pix] != ' ' || tmp[0][nb_char_for_pix + 2] != ' '))
		return (free_tab_char_with_ret_1(tmp));
	if (tmp[0][nb_char_for_pix + 3] != '#')
	{
		if ((is_this_color_built_in(tmp[0], nb_char_for_pix)))
			return (free_tab_char_with_ret_1(tmp));
	}
	else
	{
		while (i < 6 && tmp[0][nb_char_for_pix + 4 + i])
		{
			if ((tmp[0][nb_char_for_pix + 4 + i] >= '0' && tmp[0][nb_char_for_pix + 4 + i] <= '9') || (tmp[0][nb_char_for_pix + 4 + i] >= 'A' && tmp[0][nb_char_for_pix + 4 + i] <= 'F'))
				i = i + 0;
			else
				return (free_tab_char_with_ret_1(tmp));
			i++;
		}
		if (i != 6)
			return (free_tab_char_with_ret_1(tmp));
	}
	free_tab_char(tmp);
	return (0);
}

int recup_char_for_pix_or_nb_of_color(char *str, int t)
{
	char **tmp;
	char **tmp2;
	int ret;

	tmp = ft_strsplit(str, '"');
	tmp2 = ft_strsplit(tmp[0], ' ');
	ret = 0;
	if (t == 1)
		ret = ft_atoi(tmp2[2]);
	else if (t == 0)
		ret = ft_atoi(tmp2[3]);
	else if (t == 3)
			ret = ft_atoi(tmp2[0]);
	else if (t == 2)
			ret = ft_atoi(tmp2[1]);
	free_tab_char(tmp);
	free_tab_char(tmp2);
	return(ret);
}

int is_this_a_good_pixel_line(char *str, char* color_ids,  int nb_char_for_pix, int width, int height, int height_count)
{
	int i;
	int x;
	int c;
	char **tmp;

	i = 0;
	x = 0;
	c = 0;
	if(is_there_good_init_and_end_of_line(str))
	{
		if (height != height_count + 1)
			return (1);
		else if (height == height_count && str[nb_char_for_pix * width + 1] != '"')
			return (1);
	}
	tmp = ft_strsplit(str, '"');
	if ((int)ft_strlen(tmp[0]) != (width * nb_char_for_pix))
		return (free_tab_char_with_ret_1(tmp));
	while (tmp[0][i])
	{
		c = 0;
		while(color_ids[x] && tmp[0][i] && color_ids[x] == tmp[0][i] && c < nb_char_for_pix)
		{
			c++;
			x++;
			i++;
		}
		if (c == nb_char_for_pix)
		{
			x = 0;
			i = i + nb_char_for_pix;
		}
		else if (x != 0 && color_ids[x] == 0 && color_ids[x - 1] != tmp[0][i - 1])
			return (free_tab_char_with_ret_1(tmp));
		else if (c == 0)
			x = x + nb_char_for_pix;
		else
			x = x - c + nb_char_for_pix;
		i = i - c;
	}
	free_tab_char(tmp);
	return (0);
}

int check_the_construction(char *name_file)
{
	int fd;
	char *buff;
	int ret;
	int i;
	int color_list_token;
	int color_count;
	char *color_ids;
	int nb_char_for_pix;
	int nb_of_color;
	int j;
	int j2;
	int width;
	int height;
	int height_count;

	height_count = 0;
	color_count = 0;
	i = 0;
	j = 0;
	j2 = 0;
	color_list_token = 0;
	fd = open(name_file, O_RDONLY);
	if (fd < 0)
		return (1);
	while ((ret = get_next_line(fd, &buff)))
	{
		if (i < 4)
		{
			if (i == 0)
			{
				if (ft_strcmp(buff, "/* XPM */"))
					return (1);
			}
			if (i == 1)
			{
				if (check_the_static_char(buff))
					return (1);
			}
			if (i == 2)
			{
				if (ft_strcmp(buff, "/* columns rows colors chars-per-pixel */"))
					return (1);
			}
			if (i == 3)
			{
				if (check_settings(buff))
					return(1);
				if (!(color_ids = malloc_color_ids(buff)))
					return (1);
				nb_char_for_pix = recup_char_for_pix_or_nb_of_color(buff, 0);
				nb_of_color = recup_char_for_pix_or_nb_of_color(buff, 1);
				height = recup_char_for_pix_or_nb_of_color(buff, 2);
				width = recup_char_for_pix_or_nb_of_color(buff, 3);
				color_list_token = 2;
			}
		}
		if (color_list_token == 3)
		{
			if (buff[0] == '"')
			{
				if(is_this_a_good_pixel_line(buff, color_ids, nb_char_for_pix, width, height, height_count))
				{
					ft_putstr("-55-\n");
					return (1);
				}
			}
			else
			{
				if(ft_strcmp(buff, "};"))
					return (1);
			}
			height_count++;
		}
		else if (color_list_token == 1)
		{
			if (buff[0] == '/')
			{
				if (color_count != nb_of_color)
				{
					ft_error(7, NULL);
					return (1);
				}
				if(ft_strcmp(buff, "/* pixels */"))
				{
					ft_error(6, buff);
					return(1);
				}
				color_ids[j2] = 0;
				color_list_token = 3;
			}
			else
			{
				if(is_there_good_init_and_end_of_line(buff))
				{
					ft_error(8, &i);
					return (1);
				}
				if (construction_of_color_line(buff, nb_char_for_pix))
				{
					ft_error(10, &i);
					return (1);
				}
				j = 0;
				while (j != nb_char_for_pix)
				{
					color_ids[j2] = buff[j + 1];
					j++;
					j2++;
				}
				color_count++;
			}
		}
		if (color_list_token == 2)
			color_list_token = 1;
		i++;
		free(buff);
	}
	close(fd);
	free(color_ids);
	return(0);
}

int is_the_file_a_xpm(char *name_file)
{
	if (!(is_good_extension(name_file)))
	{
		ft_error(4, NULL);
		return (1);
	}
	return (check_the_construction(name_file));
}

int is_the_file_a_correct_file(char *name_file)
{
	int fd;
	char tmp[2];
	int ret;

	fd = open(name_file, O_RDONLY);
	if (fd < 0)
		return (0);
	ft_messages(2, NULL);
	ret = read(fd, tmp, 2);
	tmp[ret] = 0;
	if (tmp[0] == 0)
	{
		ft_error(5, NULL);
		return (0);
	}
	ft_messages(3, NULL);
	close(fd);
	return (1);
}

int is_only_good_char(char *name_file)
{
	int fd;
	char *buff;
	int ret;
	int i;

	fd = open(name_file, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((ret = get_next_line(fd, &buff)))
	{
		i = 0;
		while (buff[i])
		{
			if (buff[i] < 0 || buff[i] > 127)
			{
				free(buff);
				ft_error(3, NULL);
				return(0);
			}
			i++;
		}
		free(buff);
	}
	close(fd);
	return(1);
}

int is_the_file_ok(t_data *data)
{
	if (!(is_the_file_a_correct_file(data->file_name)))
	{
		exit(0);
	}
	if (!(is_only_good_char(data->file_name)))
	{
		exit(0);
	}
	ft_messages(8, NULL);
	if (is_the_file_a_xpm(data->file_name))
	{
		exit(0);
	}
	ft_messages(7, NULL);
	return(0);
}
