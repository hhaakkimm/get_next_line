/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdrakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:53:12 by aabdrakh          #+#    #+#             */
/*   Updated: 2018/09/25 17:53:14 by aabdrakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_read(char **str, int fd)
{
	int		size;
	char	*s;
	char	buf[BUFF_SIZE + 1];

	if ((size = read(fd, buf, BUFF_SIZE)) == -1)
		return (-1);
	buf[size] = '\0';
	s = *str;
	*str = ft_strjoin(*str, buf);
	if (*s != 0)
		free(s);
	return (size);
}

static int		ready(char **str, char **line, char *s)
{
	int		flag;
	char	*new;

	flag = 0;
	if (*s == '\n')
		flag = 1;
	*s = 0;
	*line = ft_strjoin("", *str);
	if (!flag)
	{
		if (!(ft_strlen(*str)))
			return (0);
		else
		{
			*str = ft_strnew(1);
			return (1);
		}
	}
	new = *str;
	*str = ft_strjoin(s + 1, "");
	free(new);
	return (flag);
}

int				get_next_line(const int fd, char **line)
{
	int			size;
	char		*s;
	static char	*str;

	if (str == 0)
		str = "";
	if (!line || BUFF_SIZE < 1)
		return (-1);
	size = BUFF_SIZE;
	while (line)
	{
		s = str;
		while (*s || size < BUFF_SIZE)
		{
			if (*s == '\n' || !(*s))
				return (ready(&str, line, s));
			s++;
		}
		size = ft_read(&str, fd);
		if (size == -1)
			return (-1);
	}
	return (0);
}
