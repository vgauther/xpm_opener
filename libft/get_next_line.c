/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:19:01 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/05 22:14:56 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_read(int fd, char **rest)
{
	int		ret;
	char	*buff;
	char	*tmp;

	if (!(buff = (char*)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = ft_strjoin(rest[fd], buff);
		free(rest[fd]);
		rest[fd] = ft_strdup(tmp);
		free(tmp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	if (ret == -1)
		return (-1);
	return (0);
}

static void	ft_free(int fd, char **rest)
{
	char *tmp;

	tmp = ft_strdup(rest[fd]);
	free(rest[fd]);
	rest[fd] = ft_strdup(ft_strchr(tmp, '\n') + 1);
	free(tmp);
}

int			get_next_line(const int fd, char **line)
{
	static char	*rest[OPEN_MAX];
	int			i;

	i = 0;
	if ((fd >= 0 && fd < OPEN_MAX) && !rest[fd])
		rest[fd] = ft_strnew(1);
	if (fd < 0 || line == NULL || fd >= OPEN_MAX || BUFF_SIZE < 1 \
		|| ft_read(fd, rest) == -1)
		return (-1);
	if (rest[fd][0] == '\0')
		return (0);
	while (rest[fd][i] != '\0' && rest[fd][i] != '\n')
		i++;
	if (rest[fd][i] == '\0' && rest[fd][i - 1] == '\n')
		return (0);
	if (rest[fd][i] == '\0')
	{
		*line = ft_strsub(rest[fd], 0, i);
		rest[fd][0] = '\0';
		return (1);
	}
	*line = ft_strsub(rest[fd], 0, i);
	ft_free(fd, rest);
	return (1);
}
