/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_the_file_ok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:52:51 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/19 01:35:02 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

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

	if ((fd = open(name_file, O_RDONLY)) < 0)
	{
		xpm_fd_error("is_the_file_a_correct_file");
		return (0);
	}
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

	if ((fd = open(name_file, O_RDONLY)) < 0)
	{
		xpm_fd_error("is_only_good_char");
		return (0);
	}
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
