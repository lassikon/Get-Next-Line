/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:56:51 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/25 13:02:51 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	d;
	size_t	s;
	char	*str;

	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	d = 0;
	while (s1[d])
	{
		str[d] = s1[d];
		d++;
	}
	s = 0;
	while (s2[s])
	{
		str[d + s] = s2[s];
		s++;
	}
	str[d + s] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*init_buff(size_t size)
{
	char	*buf;

	buf = malloc(sizeof(char) * size);
	if (buf == (NULL))
		return (buf);
	while (size > 0)
	{
		buf[size - 1] = '\0';
		size--;
	}
	return (buf);
}

void	save_leftovers(char *buf, char *leftovers)
{
	while (*buf && *buf != '\n')
		buf++;
	while (*buf)
	{
		*leftovers = *buf;
		leftovers++;
		buf++;
	}
	*leftovers = '\0';
}

void	add_to_line(char *line, char *buf, char *leftovers)
{
	while (*line)
		line++;
	if (leftovers != NULL)
	{
		while (*leftovers)
		{
			*line = *leftovers;
			*leftovers = '\0';
			line++;
			leftovers++;
		}
	}
	while (*buf && *buf != '\n')
	{
		*line = *buf;
		line++;
		buf++;
	}
	*line = '\0';
	if (*buf)
		save_leftovers(buf, leftovers);
}

char	*read_file(int fd, char *buf, char *leftovers)
{
	int			bytes_read;
	char		*line;

	line = init_buff(BUFFER_SIZE + 1);
	bytes_read = 0;
	while (bytes_read >= 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		add_to_line(line, buf, leftovers);
		if (ft_strchr(buf, '\n'))
		{
			save_leftovers(buf, leftovers);
			break ;
		}
	}
	return (line);
}

/* The read function returns the number of bytes read,
and it can return 0 if the end of the file is reached.
If an error occurs, it returns -1. */

