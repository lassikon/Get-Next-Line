/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:53:54 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/20 15:52:26 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*buf;
	char	*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = init_buff(BUFFER_SIZE + 1);
	line = read_file(fd, buf);
	return (line);
}