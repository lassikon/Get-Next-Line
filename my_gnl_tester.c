/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gnl_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:26:15 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/27 15:55:16 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	fd = open("test_text", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
	i = 3;
	while (i >= 0)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		i--;
	}
	close(fd);
	free(line);
}