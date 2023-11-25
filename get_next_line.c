/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:53:54 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/25 13:59:40 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*leftovers;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = init_buff(BUFFER_SIZE + 1);
	if (!leftovers)
		leftovers = init_buff(BUFFER_SIZE + 1);
	line = read_file(fd, buf, leftovers);
	free(buf);
	return (line);
}
/* The read function returns the number of bytes read,
and it can return 0 if the end of the file is reached.
If an error occurs, it returns -1. */