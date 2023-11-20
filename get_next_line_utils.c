/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:56:51 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/20 15:52:25 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*str_src;
	size_t	i;

	str_src = (char *)src;
	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < (dstsize - 1) && str_src[i] != '\0')
	{
		dst[i] = str_src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1);
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len + 1);
	return (str);
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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d;
	size_t	s;

	d = 0;
	s = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dst[d] && d < dstsize)
		d++;
	while ((d + s + 1) < dstsize && src[s] != '\0')
	{
		dst[d + s] = src[s];
		s++;
	}
	if (d < dstsize)
		dst[d + s] = '\0';
	return (d + ft_strlen(src));
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
/*
Locates the first occurrence of c (converted to a char)
in the string pointed to by s.
Returns a pointer to the located character, or NULL if the
character does not appear in the string.
If c == '\0', locates to the terminating '\0' of the string.
*/

char	*init_buff(size_t size)
{
	unsigned char	*buff;
	size_t			check_max;

	buff = malloc(sizeof(char) * size);
	if (buff == (NULL))
		return (buff);
	while (size > 0)
	{
		buff[size - 1] = '\0';
		size--;
	}
	return (buff);
}
int	locate_end(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
		i++;
	return (i);
}
static void	save_leftovers(char *buf, char *leftovers)
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

static void	add_to_line(char *line, char *buf, char *leftovers)
{
	while (*line)
		line++;
	if (leftovers != NULL)
	{
		while (*leftovers)
		{
			*line = *leftovers;
			line++;
			leftovers++;
		}
	}
	free(leftovers);
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

char	*read_file(int fd, char *buf)
{
	int			bytes_read;
	static char	*leftovers;
	char		*line;

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

