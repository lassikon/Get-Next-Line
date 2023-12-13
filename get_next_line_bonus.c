/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:03:26 by lkonttin          #+#    #+#             */
/*   Updated: 2023/12/13 15:39:05 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	found_newline(t_list *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->buf[i] && i < BUFFER_SIZE)
		{
			if (list->buf[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	copy_str(t_list *list, char *str)
{
	int	i;
	int	k;

	if (list == NULL)
		return ;
	k = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->buf[i] != '\0')
		{
			if (list->buf[i] == '\n')
			{
				str[k] = '\n';
				str[k + 1] = '\0';
				return ;
			}
			str[k++] = list->buf[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

int	add_to_list(t_list **list, char *buf, int fd)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_lstlast(list[fd]);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (0);
	if (last_node == NULL)
		list[fd] = new_node;
	else
		last_node->next = new_node;
	new_node->buf = buf;
	new_node->next = NULL;
	return (1);
}

int	create_list(t_list **list, int fd)
{
	int		bytes_read;
	char	*buf;

	bytes_read = 0;
	while (!found_newline(list[fd]))
	{
		buf = ft_calloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return (0);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			free(buf);
			return (1);
		}
		if (!(add_to_list(list, buf, fd)) || bytes_read < 0)
		{
			free(buf);
			return (0);
		}
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*list[OPEN_MAX];
	char			*line;
	int				str_len;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (clean_and_free(&list[fd], 0, 0), NULL);
	if (!(create_list(list, fd)))
		return (clean_and_free(&list[fd], 0, 0), NULL);
	if (list[fd] == NULL)
		return (NULL);
	str_len = len_to_newline(list[fd]);
	line = malloc(str_len + 1);
	if (line == NULL)
		return (clean_and_free(&list[fd], 0, 0), NULL);
	copy_str(list[fd], line);
	if (!(trim_list(&list[fd])))
		return (clean_and_free(&list[fd], 0, line), NULL);
	return (line);
}
