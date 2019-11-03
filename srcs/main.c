/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 00:02:27 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/03 01:05:45 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm_opener.h"

int is_the_file_a_xpm(void)
{
	ft_putstr("xxx");
	return (0);
}

int is_the_file_a_correct_file(char *name_file)
{
	int fd;

	fd = open(name_file, O_RDONLY);
	if (fd < 0)
		return (0);
	return (1);
}

int is_the_file_ok(t_data *data)
{
	is_the_file_a_correct_file(data->file_name);
	is_the_file_a_xpm();
	return(0);
}

int main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
	{
 		ft_putstr("error");
		return (0);
	}
	 data.file_name = ft_strdup(av[1]);
 	is_the_file_ok(&data);
	(void)ac;
	(void)av;
	return (0);
}
