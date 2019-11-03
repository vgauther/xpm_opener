/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 00:02:27 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/03 20:40:31 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

void ft_messages(int id, void *data)
{
	t_data *d;


	if (id == 1)
	{
		ft_putstr("Analysis in progress for : ");
		ft_putstr((char *)data);
	}
	else if (id == 2)
	{
		ft_putstr("[✓] File found");
	}
	else if (id == 3)
	{
		ft_putstr("[✓] File openable");
	}
	else if (id == 4)
	{
		d = (t_data *)data;
		ft_putstr("Data Image :\n");
		ft_putstr("  - Height : ");
		ft_putnbr(d->height_file);
		ft_putstr("\n  - Width : ");
		ft_putnbr(d->width_file);
		ft_putstr("\n  - Number of color : ");
		ft_putnbr(d->nb_of_color);
		ft_putstr("\n  - Char per pixels : ");
		ft_putnbr(d->nb_char_pix);

	}
	ft_putstr("\n");
}

void ft_error(int id, void *data)
{
	if (id == 1)
	{
		ft_putstr("error : ");
		ft_putstr("file cannont be opened");
		ft_putstr((char *)data);
	}
	else if (id == 2)
	{
		ft_putstr("Usage : ./xpm_opener [image.xpm]");
	}
	ft_putstr("\n");
}

int is_the_file_a_xpm(void)
{
	return (0);
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
		return (0);
	ft_messages(3, NULL);
	close(fd);
	return (1);
}

int is_the_file_ok(t_data *data)
{
	is_the_file_a_correct_file(data->file_name);
	is_the_file_a_xpm();
	return(0);
}

void recup_xpm_setting(t_data *data, char *str)
{
	char **tmp;
	char **tmp2;

	tmp = ft_strsplit(str, '"');
	tmp2 = ft_strsplit(tmp[0], ' ');

	data->height_file = ft_atoi(tmp2[0]);
	data->width_file = ft_atoi(tmp2[1]);
	data->nb_of_color = ft_atoi(tmp2[2]);
	data->nb_char_pix = ft_atoi(tmp2[3]);
	ft_messages(4, (void *)data);

}

void recup_colors(t_data *data, char *str)
{
	ft_putstr("\n------\n");
	ft_putstr(str);
	ft_putstr("\n------\n");
	(void)data;
}

void open_and_read_file(t_data *data)
{
	int fd;
	int ret;
	int i;
	int token_before_img;
	char *buff;
	char *tmp;

	i = 0;
	token_before_img = 0;
	fd = open(data->file_name, O_RDONLY);
	if (fd < 0)
		exit(0);
	if (!(data->file_content = ft_strnew(0)))
		exit(0);
	while ((ret = get_next_line(fd, &buff)))
	{
		//ft_putstr(buff);
		//ft_putstr("\n");
		if (i > 2)
		{
			if (i == 3)
			{
				recup_xpm_setting(data, buff);
				if (!(data->colors = malloc(sizeof(t_color) * data->nb_of_color)))
					exit(0);
			}
			if (i > 3 && buff[0] == '/')
			{
				token_before_img = 1;
			}
			if (i > 3 && token_before_img == 0)
			{
				recup_colors(data, buff);
			}
			tmp = ft_strdup(data->file_content);
			free(data->file_content);
			data->file_content = ft_strjoin(tmp, buff);
			free(tmp);
		}
		free(buff);
		i++;
	}
	//ft_putstr(data->file_content);
}

int main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
	{
		ft_error(2, NULL);
		return (0);
	}
	data.file_name = ft_strdup(av[1]);
	ft_messages(1, (void *)data.file_name);
 	is_the_file_ok(&data);
	open_and_read_file(&data);
	(void)ac;
	(void)av;
	return (0);
}
