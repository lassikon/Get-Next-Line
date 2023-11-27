/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:53:54 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/27 15:52:29 by lkonttin         ###   ########.fr       */
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

char	*trim_and_save(char *line, char **leftovers)
{
	while (*line != '\n')
		line++;
	line++;
	if (*line != '\0')
	{
		*leftovers = ft_strjoin(line, "");
		while (*line)
		{
			*line = '\0';
			line++;
		}
	}
	return (&line[0]);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*leftovers;
	int			bytes_read;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = init_buff(BUFFER_SIZE + 1);
	bytes_read = 1;
	if (!leftovers)
	{
		leftovers = init_buff(BUFFER_SIZE + 1);
		line = init_buff(BUFFER_SIZE + 1);
	}
	else
	{
		line = ft_strjoin("", leftovers);
		free(leftovers);
	}
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		line = ft_strjoin(line, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (trim_and_save(line, &leftovers));
}
/* The read function returns the number of bytes read,
and it can return 0 if the end of the file is reached.
If an error occurs, it returns -1. */