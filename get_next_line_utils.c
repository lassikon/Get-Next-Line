/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:56:51 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/27 15:14:22 by lkonttin         ###   ########.fr       */
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

/* The read function returns the number of bytes read,
and it can return 0 if the end of the file is reached.
If an error occurs, it returns -1. */

